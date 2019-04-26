concurrentDir = ./util/concurrent

link += condition \
	scheduledthreadpoolexecutor \
	threadpoolexecutor \
	threadcachedpoolexecutor \
	mutex \
	thread \
	countdownlatch \
	atomicint \
	readwritelock \
	executors \
	future \
	futuretask \
	barrier \

objs += $(outtmp)/condition.o \
	$(outtmp)/scheduledthreadpoolexecutor.o \
	$(outtmp)/threadpoolexecutor.o \
	$(outtmp)/threadcachedpoolexecutor.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/atomicint.o \
	$(outtmp)/readwritelock.o \
	$(outtmp)/executors.o \
	$(outtmp)/future.o \
	$(outtmp)/futuretask.o \
    $(outtmp)/barrier.o \


condition :$(concurrentDir)/Condition.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Condition.cpp -o $(outtmp)/condition.o

threadpoolexecutor :$(concurrentDir)/ThreadPoolExecutor.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/ThreadPoolExecutor.cpp -o $(outtmp)/threadpoolexecutor.o

threadcachedpoolexecutor :$(concurrentDir)/ThreadCachedPoolExecutor.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/ThreadCachedPoolExecutor.cpp -o $(outtmp)/threadcachedpoolexecutor.o

scheduledthreadpoolexecutor :$(concurrentDir)/ScheduledThreadPoolExecutor.cpp
		$(gcc) $(cflags) -c $(concurrentDir)/ScheduledThreadPoolExecutor.cpp -o $(outtmp)/scheduledthreadpoolexecutor.o

mutex :$(concurrentDir)/Mutex.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Mutex.cpp -o $(outtmp)/mutex.o

thread :$(concurrentDir)/Thread.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Thread.cpp -o $(outtmp)/thread.o

countdownlatch :$(concurrentDir)/CountDownLatch.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/CountDownLatch.cpp -o $(outtmp)/countdownlatch.o

atomicint :$(concurrentDir)/AtomicInteger.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/AtomicInteger.cpp -o $(outtmp)/atomicint.o

future :$(concurrentDir)/Future.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Future.cpp -o $(outtmp)/future.o	

futuretask :$(concurrentDir)/FutureTask.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/FutureTask.cpp -o $(outtmp)/futuretask.o		

barrier :$(concurrentDir)/Barrier.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Barrier.cpp -o $(outtmp)/barrier.o		

readwritelock :$(concurrentDir)/ReadWriteLock.cpp
	$(gcc) $(cflags) -std=c++11 -lpthread -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o

executors :$(concurrentDir)/Executors.cpp
	$(gcc) $(cflags) -std=c++11 -lpthread -c $(concurrentDir)/Executors.cpp -o $(outtmp)/executors.o