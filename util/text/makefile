textDir = ./util/text

link += jsonvalue \
		jsonarray \
		jsonwriter \
		jsonreader \
		inireader \
		inivalue \
		xmlreader \
		xmlvalue \
		confreader \
		confvalue \
		yamlreader \
		yamlvalue \
		yamlarray \

objs += $(outtmp)/jsonvalue.o \
		$(outtmp)/jsonarray.o \
		$(outtmp)/jsonwriter.o \
		$(outtmp)/jsonreader.o \
		$(outtmp)/inireader.o \
		$(outtmp)/inivalue.o \
		$(outtmp)/xmlreader.o \
		$(outtmp)/xmlvalue.o \
		$(outtmp)/confreader.o \
		$(outtmp)/confvalue.o \
		$(outtmp)/yamlreader.o \
		$(outtmp)/yamlvalue.o \
		$(outtmp)/yamlarray.o \

jsonvalue :$(textDir)/JsonValue.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonValue.cpp -o $(outtmp)/jsonvalue.o

jsonarray :$(textDir)/JsonArray.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonArray.cpp -o $(outtmp)/jsonarray.o

jsonwriter :$(textDir)/JsonWriter.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonWriter.cpp -o $(outtmp)/jsonwriter.o
	
jsonreader :$(textDir)/JsonReader.cpp
	$(gcc) $(cflags) -c $(textDir)/JsonReader.cpp -o $(outtmp)/jsonreader.o

inireader :$(textDir)/IniReader.cpp
	$(gcc) $(cflags) -c $(textDir)/IniReader.cpp -o $(outtmp)/inireader.o

inivalue :$(textDir)/IniValue.cpp
	$(gcc) $(cflags) -c $(textDir)/IniValue.cpp -o $(outtmp)/inivalue.o

xmlreader :$(textDir)/XmlReader.cpp
	$(gcc) $(cflags) -c $(textDir)/XmlReader.cpp -o $(outtmp)/xmlreader.o

xmlvalue :$(textDir)/XmlValue.cpp
	$(gcc) $(cflags) -c $(textDir)/XmlValue.cpp -o $(outtmp)/xmlvalue.o

confreader :$(textDir)/ConfReader.cpp
	$(gcc) $(cflags) -c $(textDir)/ConfReader.cpp -o $(outtmp)/confreader.o

confvalue :$(textDir)/ConfValue.cpp
	$(gcc) $(cflags) -c $(textDir)/ConfValue.cpp -o $(outtmp)/confvalue.o

yamlreader :$(textDir)/YamlReader.cpp
	$(gcc) $(cflags) -c $(textDir)/YamlReader.cpp -o $(outtmp)/yamlreader.o

yamlvalue :$(textDir)/YamlValue.cpp
	$(gcc) $(cflags) -c $(textDir)/YamlValue.cpp -o $(outtmp)/yamlvalue.o

yamlarray :$(textDir)/YamlArray.cpp
	$(gcc) $(cflags) -c $(textDir)/YamlArray.cpp -o $(outtmp)/yamlarray.o