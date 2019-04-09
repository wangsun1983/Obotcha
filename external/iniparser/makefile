iniparser = ./external/iniparser

cflags += -I $(iniparser)/include \

link += external_ini_dictionary \
		external_ini_parser

objs += $(outtmp)/extinidic.o \
        $(outtmp)/extiniparser.o 

external_ini_dictionary :$(iniparser)/src/dictionary.c
	cc $(cflags) -c $(iniparser)/src/dictionary.c -o $(outtmp)/extinidic.o

external_ini_parser :$(iniparser)/src/iniparser.c
	cc $(cflags) -c $(iniparser)/src/iniparser.c -o $(outtmp)/extiniparser.o

