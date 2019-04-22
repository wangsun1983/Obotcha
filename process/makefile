processDir = process

link += pipe \
		fifopipe \
		posixmq \
		localsocketclient \
		localsocketserver \
	
objs += $(outtmp)/pipe.o \
		$(outtmp)/fifopipe.o \
		$(outtmp)/posixmq.o \
		$(outtmp)/localsocketclient.o \
		$(outtmp)/localsocketserver.o \
	
pipe :$(processDir)/Pipe.cpp
	$(gcc) $(cflags) -c $(processDir)/Pipe.cpp -o $(outtmp)/pipe.o 

fifopipe :$(processDir)/FifoPipe.cpp
	$(gcc) $(cflags) -c $(processDir)/FifoPipe.cpp -o $(outtmp)/fifopipe.o 	

posixmq :$(processDir)/PosixMq.cpp
	$(gcc) $(cflags) -c $(processDir)/PosixMq.cpp -o $(outtmp)/posixmq.o

localsocketclient :$(processDir)/LocalSocketClient.cpp
	$(gcc) $(cflags) -c $(processDir)/LocalSocketClient.cpp -o $(outtmp)/localsocketclient.o 	

localsocketserver :$(processDir)/LocalSocketServer.cpp
	$(gcc) $(cflags) -c $(processDir)/LocalSocketServer.cpp -o $(outtmp)/localsocketserver.o 	

