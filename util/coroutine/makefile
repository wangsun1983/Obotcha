coroutineDir = ./util/coroutine

objs += $(outtmp)/filament.o \
		$(outtmp)/filacondition.o \
		$(outtmp)/filacroutine.o \

$(outtmp)/filament.o :$(coroutineDir)/Filament.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/Filament.cpp -o $(outtmp)/filament.o

$(outtmp)/filacondition.o :$(coroutineDir)/FilaCondition.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCondition.cpp -o $(outtmp)/filacondition.o

$(outtmp)/filacroutine.o :$(coroutineDir)/FilaCroutine.cpp
	$(cppcompiler) $(obotchacppflags) -c $(coroutineDir)/FilaCroutine.cpp -o $(outtmp)/filacroutine.o
