utilDir = ./util

include ./util/concurrent/makefile
include ./util/text/makefile
include ./util/coroutine/makefile
include ./util/handler/makefile
include ./util/time/makefile

objs += $(outtmp)/log.o \
		$(outtmp)/uuid.o \
		$(outtmp)/random.o \
		$(outtmp)/math.o \
		$(outtmp)/stacktrace.o \
		$(outtmp)/util.o \


$(outtmp)/stacktrace.o :$(utilDir)/StackTrace.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/StackTrace.cpp -o $(outtmp)/stacktrace.o

$(outtmp)/log.o :$(utilDir)/Log.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Log.cpp -o $(outtmp)/log.o

$(outtmp)/uuid.o :$(utilDir)/UUID.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/UUID.cpp -o $(outtmp)/uuid.o

$(outtmp)/random.o :$(utilDir)/Random.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Random.cpp -o $(outtmp)/random.o

$(outtmp)/math.o :$(utilDir)/Math.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Math.cpp -o $(outtmp)/math.o

$(outtmp)/util.o :$(utilDir)/Util.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Util.cpp -o $(outtmp)/util.o
