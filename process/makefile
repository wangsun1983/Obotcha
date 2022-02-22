processDir = process

objs += $(outtmp)/pipe.o \
		$(outtmp)/fifopipe.o \
		$(outtmp)/posixmq.o \
		$(outtmp)/posixsem.o \
		$(outtmp)/posixsharememory.o \
		$(outtmp)/systemsignalhandler.o \
		$(outtmp)/orpcserializable.o \


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

$(outtmp)/systemsignalhandler.o :$(processDir)/SystemSignalHandler.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/SystemSignalHandler.cpp -o $(outtmp)/systemsignalhandler.o

$(outtmp)/orpcserializable.o :$(processDir)/OrpcSerializable.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/OrpcSerializable.cpp -o $(outtmp)/orpcserializable.o
