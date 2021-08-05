concurrentDir = ./util/concurrent

objs += $(outtmp)/condition.o \
	$(outtmp)/threadscheduledpoolexecutor.o \
	$(outtmp)/threadpoolexecutor.o \
	$(outtmp)/threadcachedpoolexecutor.o \
	$(outtmp)/threadprioritypoolexecutor.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/atomicint.o \
	$(outtmp)/atomicbool.o \
	$(outtmp)/atomiclong.o \
	$(outtmp)/atomicuint64.o \
	$(outtmp)/readwritelock.o \
	$(outtmp)/executorbuilder.o \
	$(outtmp)/future.o \
	$(outtmp)/executortask.o \
    $(outtmp)/barrier.o \
	$(outtmp)/timer.o \
	$(outtmp)/spinlock.o \
	$(outtmp)/runnable.o \

$(outtmp)/runnable.o :$(concurrentDir)/Runnable.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Runnable.cpp -o $(outtmp)/runnable.o

$(outtmp)/condition.o :$(concurrentDir)/Condition.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Condition.cpp -o $(outtmp)/condition.o

$(outtmp)/threadpoolexecutor.o :$(concurrentDir)/ThreadPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadPoolExecutor.cpp -o $(outtmp)/threadpoolexecutor.o

$(outtmp)/threadcachedpoolexecutor.o :$(concurrentDir)/ThreadCachedPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadCachedPoolExecutor.cpp -o $(outtmp)/threadcachedpoolexecutor.o

$(outtmp)/threadscheduledpoolexecutor.o :$(concurrentDir)/ThreadScheduledPoolExecutor.cpp
		$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadScheduledPoolExecutor.cpp -o $(outtmp)/threadscheduledpoolexecutor.o

$(outtmp)/mutex.o :$(concurrentDir)/Mutex.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Mutex.cpp -o $(outtmp)/mutex.o

$(outtmp)/spinlock.o :$(concurrentDir)/SpinLock.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/SpinLock.cpp -o $(outtmp)/spinlock.o

$(outtmp)/thread.o :$(concurrentDir)/Thread.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Thread.cpp -o $(outtmp)/thread.o

$(outtmp)/countdownlatch.o :$(concurrentDir)/CountDownLatch.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/CountDownLatch.cpp -o $(outtmp)/countdownlatch.o

$(outtmp)/atomicint.o :$(concurrentDir)/atomic/AtomicInteger.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/atomic/AtomicInteger.cpp -o $(outtmp)/atomicint.o

$(outtmp)/atomiclong.o :$(concurrentDir)/atomic/AtomicLong.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/atomic/AtomicLong.cpp -o $(outtmp)/atomiclong.o

$(outtmp)/atomicuint64.o :$(concurrentDir)/atomic/AtomicUint64.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/atomic/AtomicUint64.cpp -o $(outtmp)/atomicuint64.o

$(outtmp)/atomicbool.o :$(concurrentDir)/atomic/AtomicBoolean.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/atomic/AtomicBoolean.cpp -o $(outtmp)/atomicbool.o

$(outtmp)/future.o :$(concurrentDir)/Future.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Future.cpp -o $(outtmp)/future.o

$(outtmp)/executortask.o :$(concurrentDir)/ExecutorTask.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ExecutorTask.cpp -o $(outtmp)/executortask.o

$(outtmp)/barrier.o :$(concurrentDir)/Barrier.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Barrier.cpp -o $(outtmp)/barrier.o

$(outtmp)/readwritelock.o :$(concurrentDir)/ReadWriteLock.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o

$(outtmp)/executorbuilder.o :$(concurrentDir)/ExecutorBuilder.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ExecutorBuilder.cpp -o $(outtmp)/executorbuilder.o

$(outtmp)/timer.o :$(concurrentDir)/Timer.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Timer.cpp -o $(outtmp)/timer.o

$(outtmp)/threadprioritypoolexecutor.o :$(concurrentDir)/ThreadPriorityPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadPriorityPoolExecutor.cpp -o $(outtmp)/threadprioritypoolexecutor.o
