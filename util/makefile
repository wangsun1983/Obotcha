utilDir = ./util

include ./util/concurrent/makefile

link += calendar \
		timezone \
		properties \
		log \
		arraylist \
		uuid \

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \
		$(outtmp)/properties.o \
		$(outtmp)/log.o \
		$(outtmp)/arraylist.o \
		$(outtmp)/uuid.o \

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

