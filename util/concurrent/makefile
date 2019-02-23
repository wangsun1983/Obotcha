
link += condition \
	executorservice \
	scheduleservice \
	mutex \
	thread \

objs += $(outtmp)/condition.o \
	$(outtmp)/executorservice.o \
	$(outtmp)/scheduleservice.o \
	$(outtmp)/mutex.o \
	$(outtmp)/thread.o \

condition :concurrent/Condition.cpp
	$(gcc) $(cflags) -c concurrent/Condition.cpp -o $(outtmp)/condition.o

executorservice :concurrent/ExecutorService.cpp
	$(gcc) $(cflags) -c concurrent/ExecutorService.cpp -o $(outtmp)/executorservice.o

scheduleservice :concurrent/ScheduleService.cpp
		$(gcc) $(cflags) -c concurrent/ScheduleService.cpp -o $(outtmp)/scheduleservice.o

mutex :concurrent/Mutex.cpp
	$(gcc) $(cflags) -c concurrent/Mutex.cpp -o $(outtmp)/mutex.o

thread :concurrent/Thread.cpp
	$(gcc) $(cflags) -c concurrent/Thread.cpp -o $(outtmp)/thread.o
