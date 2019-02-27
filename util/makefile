utilDir = ./util

include ./util/concurrent/makefile

link += calendar \
        timezone

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \

calendar :$(utilDir)/Calendar.cpp
	$(gcc) $(cflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

timezone :$(utilDir)/TimeZone.cpp
	$(gcc) $(cflags) -c $(utilDir)/TimeZone.cpp -o $(outtmp)/timezone.o
