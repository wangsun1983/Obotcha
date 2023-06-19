handlerDir = ./util/handler

objs += $(outtmp)/handler.o \
		$(outtmp)/handlerthread.o \
		$(outtmp)/looper.o \
		$(outtmp)/message.o \
		$(outtmp)/messagequeue.o 
		
		
$(outtmp)/handler.o :$(handlerDir)/Handler.cpp
	$(cppcompiler) $(obotchacppflags) -c $(handlerDir)/Handler.cpp -o $(outtmp)/handler.o

$(outtmp)/handlerthread.o :$(handlerDir)/HandlerThread.cpp
	$(cppcompiler) $(obotchacppflags) -c $(handlerDir)/HandlerThread.cpp -o $(outtmp)/handlerthread.o

$(outtmp)/looper.o :$(handlerDir)/Looper.cpp
	$(cppcompiler) $(obotchacppflags) -c $(handlerDir)/Looper.cpp -o $(outtmp)/looper.o

$(outtmp)/message.o :$(handlerDir)/Message.cpp
	$(cppcompiler) $(obotchacppflags) -c $(handlerDir)/Message.cpp -o $(outtmp)/message.o

$(outtmp)/messagequeue.o :$(handlerDir)/MessageQueue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(handlerDir)/MessageQueue.cpp -o $(outtmp)/messagequeue.o
