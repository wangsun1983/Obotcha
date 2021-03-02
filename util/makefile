utilDir = ./util

include ./util/concurrent/makefile
include ./util/text/makefile
include ./util/coroutine/makefile

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \
		$(outtmp)/properties.o \
		$(outtmp)/log.o \
		$(outtmp)/uuid.o \
		$(outtmp)/random.o \
		$(outtmp)/math.o \
		$(outtmp)/timewatcher.o \
		$(outtmp)/stacktrace.o \
		$(outtmp)/datetime.o \
		$(outtmp)/message.o \
		$(outtmp)/handler.o \
		$(outtmp)/enviroment.o \

$(outtmp)/calendar.o :$(utilDir)/Calendar.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

$(outtmp)/stacktrace.o :$(utilDir)/StackTrace.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/StackTrace.cpp -o $(outtmp)/stacktrace.o

$(outtmp)/timezone.o :$(utilDir)/TimeZone.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/TimeZone.cpp -o $(outtmp)/timezone.o

$(outtmp)/properties.o :$(utilDir)/Properties.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Properties.cpp -o $(outtmp)/properties.o

$(outtmp)/log.o :$(utilDir)/Log.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Log.cpp -o $(outtmp)/log.o

$(outtmp)/uuid.o :$(utilDir)/UUID.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/UUID.cpp -o $(outtmp)/uuid.o

$(outtmp)/random.o :$(utilDir)/Random.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Random.cpp -o $(outtmp)/random.o

$(outtmp)/math.o :$(utilDir)/Math.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Math.cpp -o $(outtmp)/math.o

$(outtmp)/timewatcher.o :$(utilDir)/TimeWatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/TimeWatcher.cpp -o $(outtmp)/timewatcher.o

$(outtmp)/datetime.o :$(utilDir)/DateTime.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/DateTime.cpp -o $(outtmp)/datetime.o

$(outtmp)/message.o :$(utilDir)/Message.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Message.cpp -o $(outtmp)/message.o

$(outtmp)/handler.o :$(utilDir)/Handler.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Handler.cpp -o $(outtmp)/handler.o

$(outtmp)/enviroment.o :$(utilDir)/Enviroment.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Enviroment.cpp -o $(outtmp)/enviroment.o

#base64 :$(utilDir)/Base64.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Base64.cpp -o $(outtmp)/base64.o
