textDir = ./util/text

link += jsonvalue \
		jsonarray \
		jsonwriter \
		jsonreader \

objs += $(outtmp)/jsonvalue.o \
		$(outtmp)/jsonarray.o \
		$(outtmp)/jsonwriter.o \
		$(outtmp)/jsonreader.o \


jsonvalue :$(textDir)/JsonValue.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonValue.cpp -o $(outtmp)/jsonvalue.o

jsonarray :$(textDir)/JsonArray.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonArray.cpp -o $(outtmp)/jsonarray.o

jsonwriter :$(textDir)/JsonWriter.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonWriter.cpp -o $(outtmp)/jsonwriter.o
	
jsonreader :$(textDir)/JsonReader.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonReader.cpp -o $(outtmp)/jsonreader.o
