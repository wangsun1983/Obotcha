iniparser = ./external/iniparser

ini_flags = -I $(iniparser)/include \

objs += $(outtmp)/extinidic.o \
        $(outtmp)/extiniparser.o

$(outtmp)/extinidic.o :$(iniparser)/src/dictionary.c
	$(ccompiler) $(cflags) $(ini_flags) -c $(iniparser)/src/dictionary.c -o $(outtmp)/extinidic.o

$(outtmp)/extiniparser.o :$(iniparser)/src/iniparser.c
	$(ccompiler) $(cflags) $(ini_flags) -c $(iniparser)/src/iniparser.c -o $(outtmp)/extiniparser.o
