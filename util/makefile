utilDir = ./util

include ./util/concurrent/makefile
include ./util/text/makefile
include ./util/coroutine/makefile

link += calendar \
		timezone \
		properties \
		log \
		arraylist \
		uuid \
		random \
		math \
		timewatcher \

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \
		$(outtmp)/properties.o \
		$(outtmp)/log.o \
		$(outtmp)/arraylist.o \
		$(outtmp)/uuid.o \
		$(outtmp)/random.o \
		$(outtmp)/math.o \
		$(outtmp)/timewatcher.o \

calendar :$(utilDir)/Calendar.cpp
	$(gcc) $(cflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

timezone :$(utilDir)/TimeZone.cpp
	$(gcc) $(cflags) -c $(utilDir)/TimeZone.cpp -o $(outtmp)/timezone.o

properties :$(utilDir)/Properties.cpp
	$(gcc) $(cflags) -c $(utilDir)/Properties.cpp -o $(outtmp)/properties.o

log :$(utilDir)/Log.cpp
	$(gcc) $(cflags) -c $(utilDir)/Log.cpp -o $(outtmp)/log.o

arraylist :$(utilDir)/ArrayList.cpp
	$(gcc) $(cflags) -c $(utilDir)/ArrayList.cpp -o $(outtmp)/arraylist.o

uuid :$(utilDir)/UUID.cpp
	$(gcc) $(cflags) -c $(utilDir)/UUID.cpp -o $(outtmp)/uuid.o

random :$(utilDir)/Random.cpp
	$(gcc) $(cflags) -c $(utilDir)/Random.cpp -o $(outtmp)/random.o

math :$(utilDir)/Math.cpp
	$(gcc) $(cflags) -c $(utilDir)/Math.cpp -o $(outtmp)/math.o

timewatcher :$(utilDir)/TimeWatcher.cpp
	$(gcc) $(cflags) -c $(utilDir)/TimeWatcher.cpp -o $(outtmp)/timewatcher.o

#base64 :$(utilDir)/Base64.cpp
#	$(gcc) $(cflags) -c $(utilDir)/Base64.cpp -o $(outtmp)/base64.o



