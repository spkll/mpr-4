#
#   build.sh -- Build It Shell Script to build Multithreaded Portable Runtime
#

CC="/usr/bin/cc"
CFLAGS="-fPIC -g -Wshorten-64-to-32 -mtune=i686"
DFLAGS="-DPIC"
IFLAGS="-Isrc -Ilinux-i686-debug/inc"
LDFLAGS="-g -ldl"
LIBS="-lpthread -lm"

${CC} -c -o linux-i686-debug/obj/dtoa.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/dtoa.c

${CC} -c -o linux-i686-debug/obj/mpr.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mpr.c

${CC} -c -o linux-i686-debug/obj/mprAsync.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprAsync.c

${CC} -c -o linux-i686-debug/obj/mprAtomic.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprAtomic.c

${CC} -c -o linux-i686-debug/obj/mprBuf.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprBuf.c

${CC} -c -o linux-i686-debug/obj/mprCache.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprCache.c

${CC} -c -o linux-i686-debug/obj/mprCmd.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprCmd.c

${CC} -c -o linux-i686-debug/obj/mprCond.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprCond.c

${CC} -c -o linux-i686-debug/obj/mprCrypt.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprCrypt.c

${CC} -c -o linux-i686-debug/obj/mprDisk.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprDisk.c

${CC} -c -o linux-i686-debug/obj/mprDispatcher.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprDispatcher.c

${CC} -c -o linux-i686-debug/obj/mprEncode.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprEncode.c

${CC} -c -o linux-i686-debug/obj/mprEpoll.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprEpoll.c

${CC} -c -o linux-i686-debug/obj/mprEvent.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprEvent.c

${CC} -c -o linux-i686-debug/obj/mprFile.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprFile.c

${CC} -c -o linux-i686-debug/obj/mprFileSystem.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprFileSystem.c

${CC} -c -o linux-i686-debug/obj/mprHash.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprHash.c

${CC} -c -o linux-i686-debug/obj/mprJSON.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprJSON.c

${CC} -c -o linux-i686-debug/obj/mprKqueue.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprKqueue.c

${CC} -c -o linux-i686-debug/obj/mprList.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprList.c

${CC} -c -o linux-i686-debug/obj/mprLock.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprLock.c

${CC} -c -o linux-i686-debug/obj/mprLog.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprLog.c

${CC} -c -o linux-i686-debug/obj/mprMem.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprMem.c

${CC} -c -o linux-i686-debug/obj/mprMime.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprMime.c

${CC} -c -o linux-i686-debug/obj/mprMixed.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprMixed.c

${CC} -c -o linux-i686-debug/obj/mprModule.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprModule.c

${CC} -c -o linux-i686-debug/obj/mprPath.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprPath.c

${CC} -c -o linux-i686-debug/obj/mprPoll.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprPoll.c

${CC} -c -o linux-i686-debug/obj/mprPrintf.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprPrintf.c

${CC} -c -o linux-i686-debug/obj/mprRomFile.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprRomFile.c

${CC} -c -o linux-i686-debug/obj/mprSelect.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprSelect.c

${CC} -c -o linux-i686-debug/obj/mprSignal.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprSignal.c

${CC} -c -o linux-i686-debug/obj/mprSocket.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprSocket.c

${CC} -c -o linux-i686-debug/obj/mprString.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprString.c

${CC} -c -o linux-i686-debug/obj/mprTest.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprTest.c

${CC} -c -o linux-i686-debug/obj/mprThread.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprThread.c

${CC} -c -o linux-i686-debug/obj/mprTime.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprTime.c

${CC} -c -o linux-i686-debug/obj/mprUnix.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprUnix.c

${CC} -c -o linux-i686-debug/obj/mprVxworks.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprVxworks.c

${CC} -c -o linux-i686-debug/obj/mprWait.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprWait.c

${CC} -c -o linux-i686-debug/obj/mprWide.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprWide.c

${CC} -c -o linux-i686-debug/obj/mprWin.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprWin.c

${CC} -c -o linux-i686-debug/obj/mprWince.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprWince.c

${CC} -c -o linux-i686-debug/obj/mprXml.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/mprXml.c

${CC} -shared -o linux-i686-debug/lib/libmpr.so ${LDFLAGS} linux-i686-debug/obj/dtoa.o linux-i686-debug/obj/mpr.o linux-i686-debug/obj/mprAsync.o linux-i686-debug/obj/mprAtomic.o linux-i686-debug/obj/mprBuf.o linux-i686-debug/obj/mprCache.o linux-i686-debug/obj/mprCmd.o linux-i686-debug/obj/mprCond.o linux-i686-debug/obj/mprCrypt.o linux-i686-debug/obj/mprDisk.o linux-i686-debug/obj/mprDispatcher.o linux-i686-debug/obj/mprEncode.o linux-i686-debug/obj/mprEpoll.o linux-i686-debug/obj/mprEvent.o linux-i686-debug/obj/mprFile.o linux-i686-debug/obj/mprFileSystem.o linux-i686-debug/obj/mprHash.o linux-i686-debug/obj/mprJSON.o linux-i686-debug/obj/mprKqueue.o linux-i686-debug/obj/mprList.o linux-i686-debug/obj/mprLock.o linux-i686-debug/obj/mprLog.o linux-i686-debug/obj/mprMem.o linux-i686-debug/obj/mprMime.o linux-i686-debug/obj/mprMixed.o linux-i686-debug/obj/mprModule.o linux-i686-debug/obj/mprPath.o linux-i686-debug/obj/mprPoll.o linux-i686-debug/obj/mprPrintf.o linux-i686-debug/obj/mprRomFile.o linux-i686-debug/obj/mprSelect.o linux-i686-debug/obj/mprSignal.o linux-i686-debug/obj/mprSocket.o linux-i686-debug/obj/mprString.o linux-i686-debug/obj/mprTest.o linux-i686-debug/obj/mprThread.o linux-i686-debug/obj/mprTime.o linux-i686-debug/obj/mprUnix.o linux-i686-debug/obj/mprVxworks.o linux-i686-debug/obj/mprWait.o linux-i686-debug/obj/mprWide.o linux-i686-debug/obj/mprWin.o linux-i686-debug/obj/mprWince.o linux-i686-debug/obj/mprXml.o ${LIBS}

${CC} -c -o linux-i686-debug/obj/benchMpr.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/benchMpr.c

${CC} -o linux-i686-debug/bin/benchMpr ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/benchMpr.o ${LIBS} -lmpr -g -ldl

${CC} -c -o linux-i686-debug/obj/runProgram.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/runProgram.c

${CC} -o linux-i686-debug/bin/runProgram ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/runProgram.o ${LIBS} -g -ldl

${CC} -c -o linux-i686-debug/obj/testArgv.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testArgv.c

${CC} -c -o linux-i686-debug/obj/testBuf.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testBuf.c

${CC} -c -o linux-i686-debug/obj/testCmd.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testCmd.c

${CC} -c -o linux-i686-debug/obj/testCond.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testCond.c

${CC} -c -o linux-i686-debug/obj/testEvent.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testEvent.c

${CC} -c -o linux-i686-debug/obj/testFile.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testFile.c

${CC} -c -o linux-i686-debug/obj/testHash.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testHash.c

${CC} -c -o linux-i686-debug/obj/testList.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testList.c

${CC} -c -o linux-i686-debug/obj/testLock.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testLock.c

${CC} -c -o linux-i686-debug/obj/testMem.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testMem.c

${CC} -c -o linux-i686-debug/obj/testMpr.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testMpr.c

${CC} -c -o linux-i686-debug/obj/testPath.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testPath.c

${CC} -c -o linux-i686-debug/obj/testSocket.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testSocket.c

${CC} -c -o linux-i686-debug/obj/testSprintf.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testSprintf.c

${CC} -c -o linux-i686-debug/obj/testThread.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testThread.c

${CC} -c -o linux-i686-debug/obj/testTime.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testTime.c

${CC} -c -o linux-i686-debug/obj/testUnicode.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/test/testUnicode.c

${CC} -o linux-i686-debug/bin/testMpr ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/testArgv.o linux-i686-debug/obj/testBuf.o linux-i686-debug/obj/testCmd.o linux-i686-debug/obj/testCond.o linux-i686-debug/obj/testEvent.o linux-i686-debug/obj/testFile.o linux-i686-debug/obj/testHash.o linux-i686-debug/obj/testList.o linux-i686-debug/obj/testLock.o linux-i686-debug/obj/testMem.o linux-i686-debug/obj/testMpr.o linux-i686-debug/obj/testPath.o linux-i686-debug/obj/testSocket.o linux-i686-debug/obj/testSprintf.o linux-i686-debug/obj/testThread.o linux-i686-debug/obj/testTime.o linux-i686-debug/obj/testUnicode.o ${LIBS} -lmpr -g -ldl

${CC} -c -o linux-i686-debug/obj/manager.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/manager.c

${CC} -o linux-i686-debug/bin/manager ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/manager.o ${LIBS} -lmpr -g -ldl

${CC} -c -o linux-i686-debug/obj/makerom.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/utils/makerom.c

${CC} -o linux-i686-debug/bin/makerom ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/makerom.o ${LIBS} -lmpr -g -ldl

${CC} -c -o linux-i686-debug/obj/charGen.o ${CFLAGS} ${DFLAGS} -Isrc -Ilinux-i686-debug/inc src/utils/charGen.c

${CC} -o linux-i686-debug/bin/chargen ${LDFLAGS} -Llinux-i686-debug/lib linux-i686-debug/obj/charGen.o ${LIBS} -lmpr -g -ldl
