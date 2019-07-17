httpparser = ./external/http_parser

cflags += -I $(httpparser)/include \

link += external_http_parser \

objs += $(outtmp)/exthttpparser.o \

external_http_parser :$(httpparser)/http_parser_cpp.cpp
	cc $(cflags) -c $(httpparser)/http_parser_cpp.cpp -o $(outtmp)/exthttpparser.o

