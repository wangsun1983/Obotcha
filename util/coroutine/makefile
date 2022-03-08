coroutineDir = ./util/coroutine

objs += $(outtmp)/filament.o \
		$(outtmp)/filacondition.o \
		$(outtmp)/filacroutine.o \
		$(outtmp)/filacroutinemgr.o \
		$(outtmp)/filamutex.o 
		
$(outtmp)/filamutex.o :$(coroutineDir)/FilaMutex.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaMutex.cpp -o $(outtmp)/filamutex.o
	
$(outtmp)/filacroutinemgr.o :$(coroutineDir)/FilaCroutineManager.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCroutineManager.cpp -o $(outtmp)/filacroutinemgr.o

$(outtmp)/filament.o :$(coroutineDir)/Filament.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/Filament.cpp -o $(outtmp)/filament.o

$(outtmp)/filacondition.o :$(coroutineDir)/FilaCondition.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCondition.cpp -o $(outtmp)/filacondition.o

$(outtmp)/filacroutine.o :$(coroutineDir)/FilaCroutine.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCroutine.cpp -o $(outtmp)/filacroutine.o
