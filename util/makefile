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
		enviroment \

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
		$(outtmp)/enviroment.o \

calendar :$(utilDir)/Calendar.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Calendar.cpp -o $(outtmp)/calendar.o

stacktrace :$(utilDir)/StackTrace.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/StackTrace.cpp -o $(outtmp)/stacktrace.o

timezone :$(utilDir)/TimeZone.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/TimeZone.cpp -o $(outtmp)/timezone.o

properties :$(utilDir)/Properties.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Properties.cpp -o $(outtmp)/properties.o

log :$(utilDir)/Log.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Log.cpp -o $(outtmp)/log.o

arraylist :$(utilDir)/ArrayList.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/ArrayList.cpp -o $(outtmp)/arraylist.o

uuid :$(utilDir)/UUID.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/UUID.cpp -o $(outtmp)/uuid.o

random :$(utilDir)/Random.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Random.cpp -o $(outtmp)/random.o

math :$(utilDir)/Math.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Math.cpp -o $(outtmp)/math.o

timewatcher :$(utilDir)/TimeWatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/TimeWatcher.cpp -o $(outtmp)/timewatcher.o

datetime :$(utilDir)/DateTime.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/DateTime.cpp -o $(outtmp)/datetime.o

datetimeparser 	:$(utilDir)/DateTimeParser.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/DateTimeParser.cpp -o $(outtmp)/datetimeparser.o

datetimeformatter :$(utilDir)/DateTimeFormatter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/DateTimeFormatter.cpp -o $(outtmp)/datetimeformatter.o

numberformatter :$(utilDir)/NumberFormatter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/NumberFormatter.cpp -o $(outtmp)/numberformatter.o

message :$(utilDir)/Message.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Message.cpp -o $(outtmp)/message.o

handler :$(utilDir)/Handler.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Handler.cpp -o $(outtmp)/handler.o	

enviroment :$(utilDir)/Enviroment.cpp
	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Enviroment.cpp -o $(outtmp)/enviroment.o

#base64 :$(utilDir)/Base64.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(utilDir)/Base64.cpp -o $(outtmp)/base64.o



