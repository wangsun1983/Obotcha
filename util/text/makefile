textDir = ./util/text

link += jsonvalue \
		jsonarray \
		jsonwriter \
		jsonreader \
		inireader \
		inivalue \
		xmlreader \
		xmlvalue \
		xmlwriter \
		xmldocument \
		confreader \
		confvalue \
		yamlreader \
		yamlvalue \
		yamlarray \
		stringformat \

objs += $(outtmp)/jsonvalue.o \
		$(outtmp)/jsonarray.o \
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
		$(outtmp)/yamlarray.o \
		$(outtmp)/stringformat.o \

jsonvalue :$(textDir)/JsonValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonValue.cpp -o $(outtmp)/jsonvalue.o

jsonarray :$(textDir)/JsonArray.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonArray.cpp -o $(outtmp)/jsonarray.o

jsonwriter :$(textDir)/JsonWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonWriter.cpp -o $(outtmp)/jsonwriter.o
	
jsonreader :$(textDir)/JsonReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/JsonReader.cpp -o $(outtmp)/jsonreader.o

inireader :$(textDir)/IniReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/IniReader.cpp -o $(outtmp)/inireader.o

inivalue :$(textDir)/IniValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/IniValue.cpp -o $(outtmp)/inivalue.o

xmlreader :$(textDir)/XmlReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlReader.cpp -o $(outtmp)/xmlreader.o

xmlwriter :$(textDir)/XmlWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlWriter.cpp -o $(outtmp)/xmlwriter.o

xmlvalue :$(textDir)/XmlValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlValue.cpp -o $(outtmp)/xmlvalue.o

xmldocument :$(textDir)/XmlDocument.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/XmlDocument.cpp -o $(outtmp)/xmldocument.o	

confreader :$(textDir)/ConfReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/ConfReader.cpp -o $(outtmp)/confreader.o

confvalue :$(textDir)/ConfValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/ConfValue.cpp -o $(outtmp)/confvalue.o

yamlreader :$(textDir)/YamlReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/YamlReader.cpp -o $(outtmp)/yamlreader.o

yamlvalue :$(textDir)/YamlValue.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/YamlValue.cpp -o $(outtmp)/yamlvalue.o

yamlarray :$(textDir)/YamlArray.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/YamlArray.cpp -o $(outtmp)/yamlarray.o

stringformat :$(textDir)/StringFormat.cpp
	$(cppcompiler) $(obotchacppflags) -c $(textDir)/StringFormat.cpp -o $(outtmp)/stringformat.o