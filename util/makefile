utilDir = ./util

include ./util/concurrent/makefile

link += calendar \
        timezone \
				properties \

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \
				$(outtmp)/properties.o \

calendar :$(utilDir)/Calendar.cpp
	$(gcc) $(cflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

timezone :$(utilDir)/TimeZone.cpp
	$(gcc) $(cflags) -c $(utilDir)/TimeZone.cpp -o $(outtmp)/timezone.o

properties :$(utilDir)/Properties.cpp
	$(gcc) $(cflags) -c $(utilDir)/Properties.cpp -o $(outtmp)/properties.o
