coroutineDir = ./util/coroutine

objs += $(outtmp)/filament.o \
		$(outtmp)/filacondition.o \
		$(outtmp)/filaroutine.o \
		$(outtmp)/filamutex.o \
		$(outtmp)/filafuture.o \
		$(outtmp)/fila.o 
		
$(outtmp)/filafuture.o :$(coroutineDir)/FilaFuture.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaFuture.cpp -o $(outtmp)/filafuture.o
		
$(outtmp)/filamutex.o :$(coroutineDir)/FilaMutex.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaMutex.cpp -o $(outtmp)/filamutex.o

$(outtmp)/fila.o :$(coroutineDir)/Fila.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/Fila.cpp -o $(outtmp)/fila.o

#$(outtmp)/filaroutinemgr.o :$(coroutineDir)/FilaRoutineManager.cpp
#	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaRoutineManager.cpp -o $(outtmp)/filaroutinemgr.o

$(outtmp)/filament.o :$(coroutineDir)/Filament.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/Filament.cpp -o $(outtmp)/filament.o

$(outtmp)/filacondition.o :$(coroutineDir)/FilaCondition.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCondition.cpp -o $(outtmp)/filacondition.o

$(outtmp)/filaroutine.o :$(coroutineDir)/FilaRoutine.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaRoutine.cpp -o $(outtmp)/filaroutine.o
