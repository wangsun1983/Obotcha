processDir = process

link += pipe \
		fifopipe \
		posixmq \
		posixsem \
		posixsharememory \
	
objs += $(outtmp)/pipe.o \
		$(outtmp)/fifopipe.o \
		$(outtmp)/posixmq.o \
		$(outtmp)/posixsem.o \
		$(outtmp)/posixsharememory.o \
	
pipe :$(processDir)/Pipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/Pipe.cpp -o $(outtmp)/pipe.o 

fifopipe :$(processDir)/FifoPipe.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/FifoPipe.cpp -o $(outtmp)/fifopipe.o 	

posixmq :$(processDir)/PosixMq.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixMq.cpp -o $(outtmp)/posixmq.o

posixsem :$(processDir)/PosixSem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixSem.cpp -o $(outtmp)/posixsem.o

posixanonymoussem :$(processDir)/PosixAnonymousSem.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixAnonymousSem.cpp -o $(outtmp)/posixanonymoussem.o

posixsharememory :$(processDir)/PosixShareMemory.cpp
	$(cppcompiler) $(obotchacppflags) -c $(processDir)/PosixShareMemory.cpp -o $(outtmp)/posixsharememory.o

