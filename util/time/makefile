timeDir = ./util/time

objs += $(outtmp)/calendar.o \
		$(outtmp)/datetime.o \
		$(outtmp)/timewatcher.o \
		$(outtmp)/timezone.o 
		
		
$(outtmp)/calendar.o :$(timeDir)/Calendar.cpp
	$(cppcompiler) $(obotchacppflags) -c $(timeDir)/Calendar.cpp -o $(outtmp)/calendar.o

$(outtmp)/datetime.o :$(timeDir)/DateTime.cpp
	$(cppcompiler) $(obotchacppflags) -c $(timeDir)/DateTime.cpp -o $(outtmp)/datetime.o

$(outtmp)/timewatcher.o :$(timeDir)/TimeWatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(timeDir)/TimeWatcher.cpp -o $(outtmp)/timewatcher.o

$(outtmp)/timezone.o :$(timeDir)/TimeZone.cpp
	$(cppcompiler) $(obotchacppflags) -c $(timeDir)/TimeZone.cpp -o $(outtmp)/timezone.o
