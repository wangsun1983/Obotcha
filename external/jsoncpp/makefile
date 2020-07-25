jsoncpp = ./external/jsoncpp


objs += $(outtmp)/extjsonreader.o \
        $(outtmp)/extjsonvalue.o \
		$(outtmp)/extjsonwriter.o

$(outtmp)/extjsonreader.o :$(jsoncpp)/json_reader.cpp
	$(cppcompiler) $(cppflags) -c $(jsoncpp)/json_reader.cpp -o $(outtmp)/extjsonreader.o

$(outtmp)/extjsonvalue.o :$(jsoncpp)/json_value.cpp
	$(cppcompiler) $(cppflags) -c $(jsoncpp)/json_value.cpp -o $(outtmp)/extjsonvalue.o

$(outtmp)/extjsonwriter.o :$(jsoncpp)/json_writer.cpp
	$(cppcompiler) $(cppflags) -c $(jsoncpp)/json_writer.cpp -o $(outtmp)/extjsonwriter.o
