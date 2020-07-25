httpparser = ./external/http_parser

http_parser_include = -I $(httpparser)/include \

objs += $(outtmp)/exthttpparser.o \

$(outtmp)/exthttpparser.o :$(httpparser)/http_parser_cpp.cpp
	$(cppcompiler) $(cppflags) $(http_parser_include) -c $(httpparser)/http_parser_cpp.cpp -o $(outtmp)/exthttpparser.o
