concurrentDir = ./util/concurrent

objs += $(outtmp)/condition.o \
	$(outtmp)/threadscheduledpoolexecutor.o \
	$(outtmp)/threadpoolexecutor.o \
	$(outtmp)/threadcachedpoolexecutor.o \
	$(outtmp)/threadprioritypoolexecutor.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/readwritelock.o \
	$(outtmp)/executors.o \
	$(outtmp)/future.o \
	$(outtmp)/futuretask.o \
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

$(outtmp)/future.o :$(concurrentDir)/Future.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Future.cpp -o $(outtmp)/future.o

$(outtmp)/futuretask.o :$(concurrentDir)/FutureTask.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/FutureTask.cpp -o $(outtmp)/futuretask.o

$(outtmp)/barrier.o :$(concurrentDir)/Barrier.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Barrier.cpp -o $(outtmp)/barrier.o

$(outtmp)/readwritelock.o :$(concurrentDir)/ReadWriteLock.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o

$(outtmp)/executors.o :$(concurrentDir)/Executors.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/Executors.cpp -o $(outtmp)/executors.o

$(outtmp)/timer.o :$(concurrentDir)/Timer.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/Timer.cpp -o $(outtmp)/timer.o

$(outtmp)/threadprioritypoolexecutor.o :$(concurrentDir)/ThreadPriorityPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/ThreadPriorityPoolExecutor.cpp -o $(outtmp)/threadprioritypoolexecutor.o
