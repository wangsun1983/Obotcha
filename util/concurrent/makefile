concurrentDir = ./util/concurrent

link += condition \
	executorservice \
	scheduleservice \
	mutex \
	thread \
	countdownlatch \
	atomicint \
	readwritelock \

objs += $(outtmp)/condition.o \
	$(outtmp)/executorservice.o \
	$(outtmp)/scheduleservice.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \
	$(outtmp)/countdownlatch.o \
	$(outtmp)/atomicint.o \
	$(outtmp)/readwritelock.o \

condition :$(concurrentDir)/Condition.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Condition.cpp -o $(outtmp)/condition.o

executorservice :$(concurrentDir)/ExecutorService.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/ExecutorService.cpp -o $(outtmp)/executorservice.o

scheduleservice :$(concurrentDir)/ScheduleService.cpp
		$(gcc) $(cflags) -c $(concurrentDir)/ScheduleService.cpp -o $(outtmp)/scheduleservice.o

mutex :$(concurrentDir)/Mutex.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Mutex.cpp -o $(outtmp)/mutex.o

thread :$(concurrentDir)/Thread.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/Thread.cpp -o $(outtmp)/thread.o

countdownlatch :$(concurrentDir)/CountDownLatch.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/CountDownLatch.cpp -o $(outtmp)/countdownlatch.o

atomicint :$(concurrentDir)/AtomicInteger.cpp
	$(gcc) $(cflags) -c $(concurrentDir)/AtomicInteger.cpp -o $(outtmp)/atomicint.o

readwritelock :$(concurrentDir)/ReadWriteLock.cpp
	$(gcc) $(cflags) -std=c++11 -lpthread -c $(concurrentDir)/ReadWriteLock.cpp -o $(outtmp)/readwritelock.o
