/**
    mprAtomic.c - Atomic operations

    Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/*********************************** Includes *********************************/

#include    "mpr.h"

/***************************** Forward Declarations ***************************/

/************************************ Code ************************************/

typedef char* pp;

void mprAtomTest() 
{
    void    *a, *b;
    int64   l;
    int     x;

    mprAtomBarrier();

    a = "1";
    mprAtomCas((void * volatile *) &a, (void*) a, "2");
    mprAssert(*(char*) a == '2');

    x = 0;
    mprAtomAdd(&x, 2);
    mprAssert(x == 2);
    mprAtomAdd(&x, -1);
    mprAssert(x == 1);

    l = 0;
    mprAtomAdd64(&l, 1);
    mprAssert(l == 1);
    mprAtomAdd64(&l, -2);
    mprAssert(l == -1);

    b = "1";
    mprAtomExchange(&b, "2");
    mprAssert(*(char*)b == '2');
}


void mprAtomBarrier()
{
    #if MACOSX
        OSMemoryBarrier();
    #elif BLD_WIN_LIKE
        MemoryBarrier();
    #elif BLD_CC_SYNC
        __sync_synchronize();
    #elif BLD_UNIX_LIKE
        asm volatile ("" : : : "memory");
    #elif MPR_CPU_IX86
        asm volatile ("lock; add %eax,0");
    #else
        mprGlobalLock();
        mprGlobalUnlock();
    #endif
}


/*
    Atomic Compare and swap a pointer with a full memory barrier
 */
int mprAtomCas(void * volatile *addr, void *expected, cvoid *value)
{
    #if MACOSX
        return OSAtomicCompareAndSwapPtrBarrier(expected, (void*) value, (void*) addr);
    #elif BLD_WIN_LIKE
        {
            void *prev;
            prev = InterlockedCompareExchangePointer(addr, (void*) value, expected);
            return expected == prev;
        }
    #elif BLD_CC_SYNC
        return __sync_bool_compare_and_swap(addr, expected, value);
    #elif BLD_CPU_ARCH == MPR_CPU_IX86
        {
            void *prev;
            asm volatile ("lock; cmpxchgl %2, %1"
                : "=a" (prev), "=m" (*addr)
                : "r" (value), "m" (*addr), "0" (expected));
            return expected == prev;
        }
    #elif BLD_CPU_ARCH == MPR_CPU_IX64
        {
            void *prev;
            asm volatile ("lock; cmpxchgq %q2, %1"
                : "=a" (prev), "=m" (*addr)
                : "r" (value), "m" (*addr),
                  "0" (expected));
            return expected == prev;
        }
    #else
        mprGlobalLock();
        if (*addr == expected) {
            *addr = value;
            return 1;
        }
        mprGlobalUnlock();
        return 0;
    #endif
}


/*
    Atomic add of a signed value. Used for add, subtract, inc, dec
 */
void mprAtomAdd(volatile int *ptr, int value)
{
    #if MACOSX
        OSAtomicAdd32(value, ptr);
    #elif BLD_WIN_LIKE
            return InterlockedExchangeAdd(ptr, value);
    #elif (BLD_CPU_ARCH == MPR_CPU_IX86 || BLD_CPU_ARCH == MPR_CPU_IX64) && 0
        asm volatile ("lock; xaddl %0,%1"
            : "=r" (value), "=m" (*ptr)
            : "0" (value), "m" (*ptr)
            : "memory", "cc");
    #else
        mprGlobalLock();
        *ptr += value;
        mprGlobalUnlock();
    #endif
}


void mprAtomAdd64(volatile int64 *ptr, int value)
{
#if MACOSX
    OSAtomicAdd64(value, ptr);
#elif BLD_WIN_LIKE && MPR_64_BIT
    return InterlockedExchangeAdd64(ptr, value);
#elif BLD_UNIX_LIKE && 0
    MOB
    asm volatile ("lock; xaddl %0,%1"
        : "=r" (value), "=m" (*ptr)
        : "0" (value), "m" (*ptr)
        : "memory", "cc");
#else
    mprGlobalLock();
    *ptr += value;
    mprGlobalUnlock();
#endif
}


void *mprAtomExchange(void * volatile *addr, cvoid *value)
{
#if MACOSX && 0
    return OSAtomicCompareAndSwapPtrBarrier(expected, value, addr);
#elif BLD_WIN_LIKE
    return InterlockedExchange(addr, value);
#elif BLD_UNIX_LIKE && 0
    return __sync_lock_test_and_set(addr, value);
    //  MOB -- COMPLETE
#else
    {
        void    *old;
        mprGlobalLock();
        old = * (void**) addr;
        *addr = (void*) value;
        mprGlobalUnlock();
        return old;
    }
#endif
}


/*
    Atomic list insertion. Inserts "item" at the "head" of the list. The "link" field is the next field in item.
 */
void mprAtomListInsert(void * volatile *head, volatile void **link, void *item)
{
    do {
        *link = *head;
    } while (mprAtomCas(head, (void*) *link, item));
}

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