processDir = process

objs += $(outtmp)/pipe.o \
		$(outtmp)/fifopipe.o \
		$(outtmp)/posixmq.o \
		$(outtmp)/posixsem.o \
		$(outtmp)/posixsharememory.o \
		$(outtmp)/signalcatcher.o \
		$(outtmp)/serializable.o \


$(outtmp)/pipe.o :$(processDir)/Pipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Pipe.cpp -o $(outtmp)/pipe.o

$(outtmp)/fifopipe.o :$(processDir)/FifoPipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/FifoPipe.cpp -o $(outtmp)/fifopipe.o

$(outtmp)/posixmq.o :$(processDir)/PosixMq.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixMq.cpp -o $(outtmp)/posixmq.o

$(outtmp)/posixsem.o :$(processDir)/PosixSem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixSem.cpp -o $(outtmp)/posixsem.o

$(outtmp)/posixanonymoussem.o :$(processDir)/PosixAnonymousSem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixAnonymousSem.cpp -o $(outtmp)/posixanonymoussem.o

$(outtmp)/posixsharememory.o :$(processDir)/PosixShareMemory.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixShareMemory.cpp -o $(outtmp)/posixsharememory.o

$(outtmp)/signalcatcher.o :$(processDir)/SignalCatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/SignalCatcher.cpp -o $(outtmp)/signalcatcher.o

$(outtmp)/serializable.o :$(processDir)/Serializable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Serializable.cpp -o $(outtmp)/serializable.o
