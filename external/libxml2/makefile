libxml2 = ./external/libxml2

libxml2_flags = -Wall  \
				-Wno-error=ignored-attributes \
				-Wno-missing-field-initializers \
				-Wno-sign-compare \
				-Wno-unused-function \
				-Wno-unused-parameter \
				-DLIBXML_THREAD_ENABLED=1 \


link += external_xml_sax \
		external_xml_entities \
		external_xml_encoding \
		external_xml_error \
		external_xml_parserInternals \
		external_xml_parser \
		external_xml_tree \
		external_xml_hash \
		external_xml_list \
		external_xml_xmlIO \
		external_xml_xmlmemory \
		external_xml_uri \
		external_xml_valid \
		external_xml_xlink \
		external_xml_debugXML \
		external_xml_xpath \
		external_xml_xpointer \
		external_xml_xinclude \
		external_xml_DOCBparser \
		external_xml_catalog \
		external_xml_globals \
		external_xml_threads \
		external_xml_c14n \
		external_xml_xmlstring \
		external_xml_buf \
		external_xml_xmlregexp \
		external_xml_xmlschemas \
		external_xml_xmlschemastypes \
		external_xml_xmlunicode \
		external_xml_xmlreader \
		external_xml_relaxng \
		external_xml_dict \
		external_xml_SAX2 \
		external_xml_xmlwriter \
		external_xml_legacy \
		external_xml_chvalid \
		external_xml_pattern \
		external_xml_xmlsave \
		external_xml_xmlmodule \
		external_xml_schematron \

objs += $(outtmp)/extxmlsax.o \
		$(outtmp)/extxmlentities.o \
		$(outtmp)/extxmlencoding.o \
		$(outtmp)/extxmlerror.o \
		$(outtmp)/extxmlparserInternals.o \
		$(outtmp)/extxmlparser.o \
		$(outtmp)/extxmltree.o \
		$(outtmp)/extxmlhash.o \
		$(outtmp)/extxmllist.o \
		$(outtmp)/extxmlxmlIO.o \
		$(outtmp)/extxmlxmlmemory.o \
		$(outtmp)/extxmluri.o \
		$(outtmp)/extxmlvalid.o \
		$(outtmp)/extxmlxlink.o \
		$(outtmp)/extxmldebugXML.o \
		$(outtmp)/extxmlxpath.o \
		$(outtmp)/extxmlxpointer.o \
		$(outtmp)/extxmlxinclude.o \
		$(outtmp)/extxmlDOCBparser.o \
		$(outtmp)/extxmlcatalog.o \
		$(outtmp)/extxmlglobals.o \
		$(outtmp)/extxmlthreads.o \
		$(outtmp)/extxmlc14n.o \
		$(outtmp)/extxmlxmlstring.o \
		$(outtmp)/extxmlbuf.o \
		$(outtmp)/extxmlxmlregexp.o \
		$(outtmp)/extxmlxmlschemas.o \
		$(outtmp)/extxmlxmlschemastypes.o \
		$(outtmp)/extxmlxmlunicode.o \
		$(outtmp)/extxmlxmlreader.o \
		$(outtmp)/extxmlrelaxng.o \
		$(outtmp)/extxmldict.o \
		$(outtmp)/extxmlSAX2.o \
		$(outtmp)/extxmlwriter.o \
		$(outtmp)/extxmllegacy.o \
		$(outtmp)/extxmlchvalid.o \
		$(outtmp)/extxmlpattern.o \
		$(outtmp)/extxmlxmlsave.o \
		$(outtmp)/extxmlxmlmodule.o \
		$(outtmp)/extxmlschematron.o \


external_xml_sax :$(libxml2)/SAX.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/SAX.c -o $(outtmp)/extxmlsax.o

external_xml_entities :$(libxml2)/entities.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/entities.c -o $(outtmp)/extxmlentities.o

external_xml_encoding :$(libxml2)/encoding.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/encoding.c -o $(outtmp)/extxmlencoding.o

external_xml_error :$(libxml2)/error.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/error.c -o $(outtmp)/extxmlerror.o

external_xml_parserInternals :$(libxml2)/parserInternals.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/parserInternals.c -o $(outtmp)/extxmlparserInternals.o

external_xml_parser :$(libxml2)/parser.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/parser.c -o $(outtmp)/extxmlparser.o

external_xml_tree :$(libxml2)/tree.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/tree.c -o $(outtmp)/extxmltree.o

external_xml_hash :$(libxml2)/hash.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/hash.c -o $(outtmp)/extxmlhash.o

external_xml_list :$(libxml2)/list.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/list.c -o $(outtmp)/extxmllist.o

external_xml_xmlIO :$(libxml2)/xmlIO.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlIO.c -o $(outtmp)/extxmlxmlIO.o

external_xml_xmlmemory :$(libxml2)/xmlmemory.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlmemory.c -o $(outtmp)/extxmlxmlmemory.o

external_xml_uri :$(libxml2)/uri.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/uri.c -o $(outtmp)/extxmluri.o

external_xml_valid :$(libxml2)/valid.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/valid.c -o $(outtmp)/extxmlvalid.o

external_xml_xlink :$(libxml2)/xlink.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xlink.c -o $(outtmp)/extxmlxlink.o

external_xml_debugXML :$(libxml2)/debugXML.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/debugXML.c -o $(outtmp)/extxmldebugXML.o

external_xml_xpath :$(libxml2)/xpath.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xpath.c -o $(outtmp)/extxmlxpath.o

external_xml_xpointer :$(libxml2)/xpointer.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xpointer.c -o $(outtmp)/extxmlxpointer.o

external_xml_xinclude :$(libxml2)/xinclude.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xinclude.c -o $(outtmp)/extxmlxinclude.o

external_xml_DOCBparser :$(libxml2)/DOCBparser.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/DOCBparser.c -o $(outtmp)/extxmlDOCBparser.o

external_xml_catalog :$(libxml2)/catalog.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/catalog.c -o $(outtmp)/extxmlcatalog.o

external_xml_globals :$(libxml2)/globals.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/globals.c -o $(outtmp)/extxmlglobals.o

external_xml_threads :$(libxml2)/threads.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/threads.c -o $(outtmp)/extxmlthreads.o

external_xml_c14n :$(libxml2)/c14n.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/c14n.c -o $(outtmp)/extxmlc14n.o

external_xml_xmlstring :$(libxml2)/xmlstring.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlstring.c -o $(outtmp)/extxmlxmlstring.o

external_xml_buf :$(libxml2)/buf.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/buf.c -o $(outtmp)/extxmlbuf.o

external_xml_xmlregexp :$(libxml2)/xmlregexp.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlregexp.c -o $(outtmp)/extxmlxmlregexp.o

external_xml_xmlschemas :$(libxml2)/xmlschemas.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlschemas.c -o $(outtmp)/extxmlxmlschemas.o

external_xml_xmlschemastypes :$(libxml2)/xmlschemastypes.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlschemastypes.c -o $(outtmp)/extxmlxmlschemastypes.o

external_xml_xmlunicode :$(libxml2)/xmlunicode.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlunicode.c -o $(outtmp)/extxmlxmlunicode.o

external_xml_xmlreader :$(libxml2)/xmlreader.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlreader.c -o $(outtmp)/extxmlxmlreader.o

external_xml_relaxng :$(libxml2)/relaxng.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/relaxng.c -o $(outtmp)/extxmlrelaxng.o

external_xml_dict :$(libxml2)/dict.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/dict.c -o $(outtmp)/extxmldict.o

external_xml_SAX2 :$(libxml2)/SAX2.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/SAX2.c -o $(outtmp)/extxmlSAX2.o

external_xml_xmlwriter :$(libxml2)/xmlwriter.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlwriter.c -o $(outtmp)/extxmlwriter.o

external_xml_legacy :$(libxml2)/legacy.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/legacy.c -o $(outtmp)/extxmllegacy.o

external_xml_chvalid :$(libxml2)/chvalid.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/chvalid.c -o $(outtmp)/extxmlchvalid.o

external_xml_pattern :$(libxml2)/pattern.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/pattern.c -o $(outtmp)/extxmlpattern.o

external_xml_xmlsave :$(libxml2)/xmlsave.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlsave.c -o $(outtmp)/extxmlxmlsave.o		

external_xml_pattern :$(libxml2)/pattern.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/pattern.c -o $(outtmp)/extxmlpattern.o		

external_xml_xmlmodule :$(libxml2)/xmlmodule.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/xmlmodule.c -o $(outtmp)/extxmlxmlmodule.o		

external_xml_pattern :$(libxml2)/pattern.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/pattern.c -o $(outtmp)/extxmlpattern.o		

external_xml_schematron :$(libxml2)/schematron.c
	cc $(cflags) $(libxml2_flags) -c $(libxml2)/schematron.c -o $(outtmp)/extxmlschematron.o					