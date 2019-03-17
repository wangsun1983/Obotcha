jsoncpp = ./external/jsoncpp

link += external_json_reader \
		external_json_value \
		external_json_writer \

objs += $(outtmp)/extjsonreader.o \
        $(outtmp)/extjsonvalue.o \
		$(outtmp)/extjsonwriter.o 

external_json_reader :$(jsoncpp)/json_reader.cpp
	$(gcc) $(cflags) -c $(jsoncpp)/json_reader.cpp -o $(outtmp)/extjsonreader.o

external_json_value :$(jsoncpp)/json_value.cpp
	$(gcc) $(cflags) -c $(jsoncpp)/json_value.cpp -o $(outtmp)/extjsonvalue.o

external_json_writer :$(jsoncpp)/json_writer.cpp
	$(gcc) $(cflags) -c $(jsoncpp)/json_writer.cpp -o $(outtmp)/extjsonwriter.o