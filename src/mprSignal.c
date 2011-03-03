/**
    mprSignal.c - Signal handling for Unix systems

    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/*********************************** Includes *********************************/

#include    "mpr.h"

#if BLD_UNIX_LIKE

/*********************************** Forwards *********************************/

static void manageSignal(MprSignal *sp, int flags);
static void manageSignalService(MprSignalService *ssp, int flags);
static void signalEvent(MprSignal *sp, MprEvent *event);
static void signalHandler(int signo, siginfo_t *info, void *arg);
static void unhookSignal(int signo);

/************************************ Code ************************************/

MprSignalService *mprCreateSignalService()
{
    MprSignalService    *ssp;

    if ((ssp = mprAllocObj(MprSignalService, manageSignalService)) == 0) {
        return 0;
    }
    ssp->mutex = mprCreateLock();
    ssp->signals = mprAllocZeroed(sizeof(MprSignal*) * MPR_MAX_SIGNALS);
    return ssp;
}


static void manageSignalService(MprSignalService *ssp, int flags)
{
    if (flags & MPR_MANAGE_MARK) {
        mprMark(ssp->mutex);
        mprMark(ssp->signals);
#if UNUSED
        for (i = 0; i < MPR_MAX_SIGNALS; i++) {
            if ((sp = ssp->signals[i]) != 0) {
                mprMark(sp);
            }
        }
#endif
    }
}


void mprStopSignalService()
{
    int     i;

    for (i = 0; i < MPR_MAX_SIGNALS; i++) {
        unhookSignal(i);
    }
}


/*
    Signals are hooked on demand and remain till the Mpr is destroyed
 */
static void hookSignal(int signo, MprSignal *sp)
{
    MprSignalService    *ssp;
    struct sigaction    act, old;
    int                 rc;

    ssp = MPR->signalService;
    lock(ssp);
    rc = sigaction(signo, 0, &old);
    if (rc == 0 && old.sa_sigaction != signalHandler) {
        sp->sigaction = old.sa_sigaction;
        memset(&act, 0, sizeof(act));
        act.sa_sigaction = signalHandler;
        sigfillset(&act.sa_mask);
        if (sigaction(signo, &act, 0) != 0) {
            mprError("Can't add signal %d, errno %d", mprGetOsError());
        }
    }
    unlock(ssp);
}


static void unhookSignal(int signo)
{
    MprSignalService    *ssp;
    struct sigaction    act;

    ssp = MPR->signalService;
    lock(ssp);
    sigaction(signo, 0, &act);
    if (act.sa_sigaction == signalHandler) {
        act.sa_sigaction = ssp->prior[signo];
        sigaction(signo, &act, 0);
    }
    unlock(ssp);
}


static void maskSignal(int signo)
{
    sigset_t    set;

    sigprocmask(0, 0, &set);
    sigaddset(&set, signo);
    sigprocmask(SIG_BLOCK, &set, 0);
}


static void unmaskSignal(int signo)
{
    sigset_t    set;

    sigprocmask(0, 0, &set);
    sigaddset(&set, signo);
    sigprocmask(SIG_UNBLOCK, &set, 0);
}


/*
    Actual signal handler - must be async-safe. Do very, very little here. Just set a global flag and wakeup
    the wait service (mprWakeWaitService is async safe).
    WARNING: Don't put memory allocation or logging here.
 */
static void signalHandler(int signo, siginfo_t *info, void *arg)
{
    MprSignalService    *ssp;
    MprSignalInfo       *ip;

    if (signo < 0 || signo >= MPR_MAX_SIGNALS || MPR == 0) {
        return;
    }
    ssp = MPR->signalService;
    maskSignal(signo);
    ip = &ssp->info[signo];
    ip->siginfo = *info;
    ip->arg = arg;
    ip->triggered = 1;
    ssp->hasSignals = 1;
    mprWakeWaitService();
}


static void linkSignalHandler(MprSignal *sp)
{
    MprSignalService    *ssp;

    ssp = MPR->signalService;
    lock(ssp);
    sp->next = ssp->signals[sp->signo];
    ssp->signals[sp->signo] = sp;
    unlock(ssp);
}


static void unlinkSignalHandler(MprSignal *sp)
{
    MprSignalService    *ssp;
    MprSignal           *np, *prev;

    ssp = MPR->signalService;
    lock(ssp);
    for (prev = 0, np = ssp->signals[sp->signo]; np; np = np->next) {
        if (sp == np) {
            if (prev) {
                prev->next = sp->next;
            } else {
                ssp->signals[sp->signo] = 0;
            }
            break;
        }
        prev = np;
    }
    sp->next = 0;
    unlock(ssp);
}


/*
    Add a safe-signal handler. This creates a signal handler that will run from a dispatcher without the
    normal async-safe strictures of normal signal handlers. This manages a next of signal handlers and ensures
    that prior handlers will be called appropriately.
 */
MprSignal *mprAddSignalHandler(int signo, void *handler, void *data, MprDispatcher *dispatcher, int flags)
{
    MprSignal           *sp;
    MprSignalService    *ssp;

    ssp = MPR->signalService;
    if (signo < 0 || signo >= MPR_MAX_SIGNALS) {
        mprError("Bad signal: %d", signo);
        return 0;
    }
    if (!(flags & MPR_SIGNAL_BEFORE)) {
        flags |= MPR_SIGNAL_AFTER;
    }
    if ((sp = mprAllocObj(MprSignal, manageSignal)) == 0) {
        return 0;
    }
    sp->signo = signo;
    sp->flags = flags;
    sp->handler = handler;
    sp->dispatcher = dispatcher;
    sp->data = data;
    linkSignalHandler(sp);
    hookSignal(signo, sp);
    return sp;
}


static void manageSignal(MprSignal *sp, int flags)
{
    MprSignalService    *ssp;
    
    ssp = MPR->signalService;
    if (flags & MPR_MANAGE_MARK) {
        mprMark(sp->dispatcher);
        mprMark(sp->data);
        /* Don't mark next as it will prevent other signal handlers being reclaimed */
    }
}


void mprRemoveSignalHandler(MprSignal *sp)
{
    if (sp) {
        unlinkSignalHandler(sp);
    }
}


/*
    Called by mprServiceEvents after a signal has been received. Create an event and queue on the appropriate dispatcher
 */
void mprServiceSignals()
{
    MprSignalService    *ssp;
    MprSignal           *sp;
    MprSignalInfo       *ip;
    int                 signo;

    ssp = MPR->signalService;
    ssp->hasSignals = 0;
    for (ip = ssp->info; ip < &ssp->info[MPR_MAX_SIGNALS]; ip++) {
        if (ip->triggered) {
            ip->triggered = 0;
            signo = ip->siginfo.si_signo;
            mprAssert(0 <= signo && signo < MPR_MAX_SIGNALS);
            mprLog(5, "Caught signal %d", signo);
            sp = ssp->signals[signo];
            if (sp) {
                sp->info = *ip;
                mprCreateEvent(sp->dispatcher, "signalEvent", 0, signalEvent, sp, 0);
            }
            unmaskSignal(signo);
        }
    }
}


/*
    Invoke the next signal handler. Runs from the dispatcher so signal handlers don't have to be async-safe.
 */
static void signalEvent(MprSignal *sp, MprEvent *event)
{
    mprAssert(sp);
    mprAssert(event);

    mprLog(7, "signalEvent signo %d, flags %x", sp->signo, sp->flags);

    if (sp->flags & MPR_SIGNAL_BEFORE) {
        (sp->handler)(sp->data, sp);
    } 
    if (sp->sigaction) {
        (sp->sigaction)(sp->signo, &sp->info.siginfo, sp->info.arg);
    }
    if (sp->flags & MPR_SIGNAL_AFTER) {
        (sp->handler)(sp->data, sp);
    }
    if ((sp = sp->next) != 0) {
        /* Create new event for each handler so we get the right dispatcher for each */
        mprCreateEvent(sp->dispatcher, "signalEvent", 0, signalEvent, sp, 0);
    }
}


/*
    Standard signal handler.  Ignore signals SIGPIPE and SIGXFSZ. 
    Do graceful shutdown for SIGTERM, immediate exit for SIGABRT.  All other signals do normal exit.
 */
static void standardSignalHandler(void *ignored, MprSignal *sp)
{
    mprLog(7, "standardSignalHandler signo %d, flags %x", sp->signo, sp->flags);
#if DEBUG_IDE
    if (sp->signo == SIGINT) return;
#endif
    mprLog(2, "Received signal %d", sp->signo);
    if (sp->signo == SIGTERM) {
        mprLog(1, "Executing a graceful exit. Waiting for all requests to complete.");
        mprTerminate(MPR_EXIT_GRACEFUL);

    } else if (sp->signo == SIGABRT) {
        mprTerminate(MPR_EXIT_IMMEDIATE);

    } else if (sp->signo == SIGPIPE || sp->signo == SIGXFSZ) {
        /* Ignore */

    } else {
        mprLog(1, "Exiting ...");
        mprTerminate(MPR_EXIT_DEFAULT);
    }
}


void mprAddStandardSignals()
{
    mprAddSignalHandler(SIGINT,  standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
    mprAddSignalHandler(SIGQUIT, standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
    mprAddSignalHandler(SIGTERM, standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
    mprAddSignalHandler(SIGUSR1, standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
    mprAddSignalHandler(SIGPIPE, standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
#if SIGXFSZ
    mprAddSignalHandler(SIGXFSZ, standardSignalHandler, 0, 0, MPR_SIGNAL_AFTER);
#endif
}


#else /* BLD_UNIX_LIKE */
    MprSignalService *mprCreateSignalService() { return mprAlloc(0); }
    int mprRemoveSignalHandler(MprSignal *sp) { return 0; }
    void mprServiceSignals() {}
#endif /* BLD_UNIX_LIKE */

/*
    @copy   default

    Copyright (c) Embedthis Software LLC, 2003-2011. All Rights Reserved.
    Copyright (c) Michael O'Brien, 1993-2011. All Rights Reserved.

    This software is distributed under commercial and open source licenses.
    You may use the GPL open source license described below or you may acquire
    a commercial license from Embedthis Software. You agree to be fully bound
    by the terms of either license. Consult the LICENSE.TXT distributed with
    this software for full details.

    This software is open source; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version. See the GNU General Public License for more
    details at: http://www.embedthis.com/downloads/gplLicense.html

    This program is distributed WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    This GPL license does NOT permit incorporating this software into
    proprietary programs. If you are unable to comply with the GPL, you must
    acquire a commercial license to use this software. Commercial licenses
    for this software and support services are available from Embedthis
    Software at http://www.embedthis.com

    Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */