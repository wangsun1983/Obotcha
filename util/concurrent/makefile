concurrentDir = ./util/concurrent

link += condition \
	scheduledthreadpoolexecutor \
	threadpoolexecutor \
	threadcachedpoolexecutor \
	prioritypoolexecutor \
	mutex \
	thread \
	countdownlatch \
	atomicint \
	atomicbool \
	atomiclong \
	atomicuint64 \
	readwritelock \
	executors \
	future \
	futuretask \
	barrier \
	timer \
	executordestructorexception \

objs += $(outtmp)/condition.o \
	$(outtmp)/scheduledthreadpoolexecutor.o \
	$(outtmp)/threadpoolexecutor.o \
	$(outtmp)/threadcachedpoolexecutor.o \
	$(outtmp)/prioritypoolexecutor.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/atomicint.o \
	$(outtmp)/atomicbool.o \
	$(outtmp)/atomiclong.o \
	$(outtmp)/atomicuint64.o \
	$(outtmp)/readwritelock.o \
	$(outtmp)/executors.o \
	$(outtmp)/future.o \
	$(outtmp)/futuretask.o \
    $(outtmp)/barrier.o \
	$(outtmp)/timer.o \
	$(outtmp)/executordestructorexception.o \


condition :$(concurrentDir)/Condition.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Condition.cpp -o $(outtmp)/condition.o

threadpoolexecutor :$(concurrentDir)/ThreadPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadPoolExecutor.cpp -o $(outtmp)/threadpoolexecutor.o

threadcachedpoolexecutor :$(concurrentDir)/ThreadCachedPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/ThreadCachedPoolExecutor.cpp -o $(outtmp)/threadcachedpoolexecutor.o

scheduledthreadpoolexecutor :$(concurrentDir)/ScheduledThreadPoolExecutor.cpp
		$(cppcompiler) $(cppflags) -c $(concurrentDir)/ScheduledThreadPoolExecutor.cpp -o $(outtmp)/scheduledthreadpoolexecutor.o

mutex :$(concurrentDir)/Mutex.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Mutex.cpp -o $(outtmp)/mutex.o

thread :$(concurrentDir)/Thread.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Thread.cpp -o $(outtmp)/thread.o

countdownlatch :$(concurrentDir)/CountDownLatch.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/CountDownLatch.cpp -o $(outtmp)/countdownlatch.o

atomicint :$(concurrentDir)/AtomicInteger.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicInteger.cpp -o $(outtmp)/atomicint.o

atomiclong :$(concurrentDir)/AtomicLong.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicLong.cpp -o $(outtmp)/atomiclong.o

atomicuint64 :$(concurrentDir)/AtomicUint64.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicUint64.cpp -o $(outtmp)/atomicuint64.o

atomicbool :$(concurrentDir)/AtomicBoolean.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/AtomicBoolean.cpp -o $(outtmp)/atomicbool.o

future :$(concurrentDir)/Future.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Future.cpp -o $(outtmp)/future.o	

futuretask :$(concurrentDir)/FutureTask.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/FutureTask.cpp -o $(outtmp)/futuretask.o		

barrier :$(concurrentDir)/Barrier.cpp
	$(cppcompiler) $(cppflags) -c $(concurrentDir)/Barrier.cpp -o $(outtmp)/barrier.o		

readwritelock :$(concurrentDir)/ReadWriteLock.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o

executors :$(concurrentDir)/Executors.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/Executors.cpp -o $(outtmp)/executors.o

executordestructorexception :$(concurrentDir)/ExecutorDestructorException.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/ExecutorDestructorException.cpp -o $(outtmp)/executordestructorexception.o

timer :$(concurrentDir)/Timer.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/Timer.cpp -o $(outtmp)/timer.o

prioritypoolexecutor :$(concurrentDir)/PriorityPoolExecutor.cpp
	$(cppcompiler) $(cppflags) -std=c++11 -lpthread -c $(concurrentDir)/PriorityPoolExecutor.cpp -o $(outtmp)/prioritypoolexecutor.o