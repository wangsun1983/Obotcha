httpparser = ./external/http_parser

http_parser_include = -I $(httpparser)/include \

link += external_http_parser \

objs += $(outtmp)/exthttpparser.o \

external_http_parser :$(httpparser)/http_parser_cpp.cpp
	$(cppcompiler) $(cppflags) $(http_parser_include) -c $(httpparser)/http_parser_cpp.cpp -o $(outtmp)/exthttpparser.o

