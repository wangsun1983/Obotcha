processDir = process

objs += $(outtmp)/pipe.o \
		$(outtmp)/fifopipe.o \
		$(outtmp)/processmq.o \
		$(outtmp)/processsem.o \
		$(outtmp)/sharememory.o \
		$(outtmp)/signalcatcher.o \
		$(outtmp)/serializable.o \
		$(outtmp)/processmutex.o \
		$(outtmp)/processreadwritelock.o \
		$(outtmp)/processcondition.o \
		$(outtmp)/process.o \
				

$(outtmp)/pipe.o :$(processDir)/Pipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Pipe.cpp -o $(outtmp)/pipe.o

$(outtmp)/fifopipe.o :$(processDir)/FifoPipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/FifoPipe.cpp -o $(outtmp)/fifopipe.o

$(outtmp)/processmq.o :$(processDir)/ProcessMq.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ProcessMq.cpp -o $(outtmp)/processmq.o

$(outtmp)/processmutex.o :$(processDir)/ProcessMutex.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ProcessMutex.cpp -o $(outtmp)/processmutex.o

$(outtmp)/processcondition.o :$(processDir)/ProcessCondition.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ProcessCondition.cpp -o $(outtmp)/processcondition.o

$(outtmp)/processreadwritelock.o :$(processDir)/ProcessReadWriteLock.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ProcessReadWriteLock.cpp -o $(outtmp)/processreadwritelock.o

$(outtmp)/processsem.o :$(processDir)/ProcessSem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ProcessSem.cpp -o $(outtmp)/processsem.o

$(outtmp)/sharememory.o :$(processDir)/ShareMemory.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/ShareMemory.cpp -o $(outtmp)/sharememory.o

$(outtmp)/signalcatcher.o :$(processDir)/SignalCatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/SignalCatcher.cpp -o $(outtmp)/signalcatcher.o

$(outtmp)/serializable.o :$(processDir)/Serializable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Serializable.cpp -o $(outtmp)/serializable.o

$(outtmp)/process.o :$(processDir)/Process.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Process.cpp -o $(outtmp)/process.o
