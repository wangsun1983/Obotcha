textDir = ./util/text

objs += $(outtmp)/jsonvalue.o \
		$(outtmp)/jsonwriter.o \
		$(outtmp)/jsonreader.o \
		$(outtmp)/inireader.o \
		$(outtmp)/inivalue.o \
		$(outtmp)/xmlreader.o \
		$(outtmp)/xmlwriter.o \
		$(outtmp)/xmlvalue.o \
		$(outtmp)/xmldocument.o \
		$(outtmp)/confreader.o \
		$(outtmp)/confvalue.o \
		$(outtmp)/yamlreader.o \
		$(outtmp)/yamlvalue.o \

$(outtmp)/jsonvalue.o :$(textDir)/JsonValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonValue.cpp -o $(outtmp)/jsonvalue.o

$(outtmp)/jsonwriter.o :$(textDir)/JsonWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonWriter.cpp -o $(outtmp)/jsonwriter.o

$(outtmp)/jsonreader.o :$(textDir)/JsonReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonReader.cpp -o $(outtmp)/jsonreader.o

$(outtmp)/inireader.o :$(textDir)/IniReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/IniReader.cpp -o $(outtmp)/inireader.o

$(outtmp)/inivalue.o :$(textDir)/IniValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/IniValue.cpp -o $(outtmp)/inivalue.o

$(outtmp)/xmlreader.o :$(textDir)/XmlReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlReader.cpp -o $(outtmp)/xmlreader.o

$(outtmp)/xmlwriter.o :$(textDir)/XmlWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlWriter.cpp -o $(outtmp)/xmlwriter.o

$(outtmp)/xmlvalue.o :$(textDir)/XmlValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlValue.cpp -o $(outtmp)/xmlvalue.o

$(outtmp)/xmldocument.o :$(textDir)/XmlDocument.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlDocument.cpp -o $(outtmp)/xmldocument.o

$(outtmp)/confreader.o :$(textDir)/ConfReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/ConfReader.cpp -o $(outtmp)/confreader.o

$(outtmp)/confvalue.o :$(textDir)/ConfValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/ConfValue.cpp -o $(outtmp)/confvalue.o

$(outtmp)/yamlreader.o :$(textDir)/YamlReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/YamlReader.cpp -o $(outtmp)/yamlreader.o

$(outtmp)/yamlvalue.o :$(textDir)/YamlValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/YamlValue.cpp -o $(outtmp)/yamlvalue.o
