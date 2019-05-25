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
	$(gcc) $(cflags) -c $(processDir)/Pipe.cpp -o $(outtmp)/pipe.o 

fifopipe :$(processDir)/FifoPipe.cpp
	$(gcc) $(cflags) -c $(processDir)/FifoPipe.cpp -o $(outtmp)/fifopipe.o 	

posixmq :$(processDir)/PosixMq.cpp
	$(gcc) $(cflags) -c $(processDir)/PosixMq.cpp -o $(outtmp)/posixmq.o

posixsem :$(processDir)/PosixSem.cpp
	$(gcc) $(cflags) -c $(processDir)/PosixSem.cpp -o $(outtmp)/posixsem.o

posixanonymoussem :$(processDir)/PosixAnonymousSem.cpp
	$(gcc) $(cflags) -c $(processDir)/PosixAnonymousSem.cpp -o $(outtmp)/posixanonymoussem.o

posixsharememory :$(processDir)/PosixShareMemory.cpp
	$(gcc) $(cflags) -c $(processDir)/PosixShareMemory.cpp -o $(outtmp)/posixsharememory.o

