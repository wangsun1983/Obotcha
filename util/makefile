utilDir = ./util

include ./util/concurrent/makefile
include ./util/text/makefile
include ./util/coroutine/makefile
include ./util/sql/makefile

link += calendar \
		timezone \
		properties \
		log \
		arraylist \
		uuid \
		random \
		math \
		timewatcher \
		stacktrace \
		datetime \
		datetimeparser \
		datetimeformatter \
		numberformatter \
		message \
		handler \

objs += $(outtmp)/calendar.o \
        $(outtmp)/timezone.o \
		$(outtmp)/properties.o \
		$(outtmp)/log.o \
		$(outtmp)/arraylist.o \
		$(outtmp)/uuid.o \
		$(outtmp)/random.o \
		$(outtmp)/math.o \
		$(outtmp)/timewatcher.o \
		$(outtmp)/stacktrace.o \
		$(outtmp)/datetime.o \
		$(outtmp)/datetimeparser.o \
		$(outtmp)/datetimeformatter.o \
		$(outtmp)/numberformatter.o \
		$(outtmp)/message.o \
		$(outtmp)/handler.o \

calendar :$(utilDir)/Calendar.cpp
	$(gcc) $(cflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

stacktrace :$(utilDir)/StackTrace.cpp
	$(gcc) $(cflags) -c $(utilDir)/StackTrace.cpp -o $(outtmp)/stacktrace.o

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

datetime :$(utilDir)/DateTime.cpp
	$(gcc) $(cflags) -c $(utilDir)/DateTime.cpp -o $(outtmp)/datetime.o

datetimeparser 	:$(utilDir)/DateTimeParser.cpp
	$(gcc) $(cflags) -c $(utilDir)/DateTimeParser.cpp -o $(outtmp)/datetimeparser.o

datetimeformatter :$(utilDir)/DateTimeFormatter.cpp
	$(gcc) $(cflags) -c $(utilDir)/DateTimeFormatter.cpp -o $(outtmp)/datetimeformatter.o

numberformatter :$(utilDir)/NumberFormatter.cpp
	$(gcc) $(cflags) -c $(utilDir)/NumberFormatter.cpp -o $(outtmp)/numberformatter.o

message :$(utilDir)/Message.cpp
	$(gcc) $(cflags) -c $(utilDir)/Message.cpp -o $(outtmp)/message.o

handler :$(utilDir)/Handler.cpp
	$(gcc) $(cflags) -c $(utilDir)/Handler.cpp -o $(outtmp)/handler.o	
#base64 :$(utilDir)/Base64.cpp
#	$(gcc) $(cflags) -c $(utilDir)/Base64.cpp -o $(outtmp)/base64.o



