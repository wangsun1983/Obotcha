concurrentDir = ./util/concurrent

objs += $(outtmp)/condition.o \
	$(outtmp)/threadscheduledpoolexecutor.o \
	$(outtmp)/threadpoolexecutor.o \
	$(outtmp)/threadcachedpoolexecutor.o \
	$(outtmp)/threadprioritypoolexecutor.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/atomicbool.o \
	$(outtmp)/atomicnumber.o \
	$(outtmp)/readwritelock.o \
	$(outtmp)/executorbuilder.o \
	$(outtmp)/future.o \
	$(outtmp)/executortask.o \
	$(outtmp)/executor.o \
    $(outtmp)/barrier.o \
	$(outtmp)/spinlock.o \
	$(outtmp)/executorresult.o \
	$(outtmp)/autolock.o 


$(outtmp)/executorresult.o :$(concurrentDir)/ExecutorResult.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ExecutorResult.cpp -o $(outtmp)/executorresult.o

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

$(outtmp)/atomicnumber.o :$(concurrentDir)/AtomicNumber.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicNumber.cpp -o $(outtmp)/atomicnumber.o

$(outtmp)/atomicbool.o :$(concurrentDir)/AtomicBoolean.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicBoolean.cpp -o $(outtmp)/atomicbool.o

$(outtmp)/future.o :$(concurrentDir)/Future.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Future.cpp -o $(outtmp)/future.o

$(outtmp)/executortask.o :$(concurrentDir)/ExecutorTask.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ExecutorTask.cpp -o $(outtmp)/executortask.o

$(outtmp)/executor.o :$(concurrentDir)/Executor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Executor.cpp -o $(outtmp)/executor.o

$(outtmp)/barrier.o :$(concurrentDir)/Barrier.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Barrier.cpp -o $(outtmp)/barrier.o

$(outtmp)/readwritelock.o :$(concurrentDir)/ReadWriteLock.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o

$(outtmp)/executorbuilder.o :$(concurrentDir)/ExecutorBuilder.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ExecutorBuilder.cpp -o $(outtmp)/executorbuilder.o

$(outtmp)/threadprioritypoolexecutor.o :$(concurrentDir)/ThreadPriorityPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadPriorityPoolExecutor.cpp -o $(outtmp)/threadprioritypoolexecutor.o

#$(outtmp)/runnable.o :$(concurrentDir)/Runnable.cpp
#	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Runnable.cpp -o $(outtmp)/runnable.o

$(outtmp)/autolock.o :$(concurrentDir)/AutoLock.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AutoLock.cpp -o $(outtmp)/autolock.o
