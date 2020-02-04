ioDir = io

link += file \
	fileinputstream \
	inputstream \
	outputstream \
	fileoutputstream \
	printstream \
	zipfilestream \
	zipmemorystream \
	filewatcher \
	memoryfileinputstream \
	memoryfileoutputstream \
	libraryfileinputstream \
	filenodereader \
	epollfileobserver \
	bytearrayreader \
	bytearraywriter \
	filenotfoundexception \
	stringreader \
	byteringarrayreader \


objs += $(outtmp)/file.o \
	$(outtmp)/fileinputstream.o \
	$(outtmp)/inputstream.o \
	$(outtmp)/outputstream.o \
	$(outtmp)/fileoutputstream.o \
	$(outtmp)/printstream.o \
	$(outtmp)/zipfilestream.o \
	$(outtmp)/zipmemorystream.o \
	$(outtmp)/filewatcher.o \
	$(outtmp)/memoryfileinputstream.o \
	$(outtmp)/memoryfileoutputstream.o \
	$(outtmp)/libraryfileinputstream.o \
	$(outtmp)/filenodereader.o \
	$(outtmp)/epollfileobserver.o \
	$(outtmp)/bytearrayreader.o \
	$(outtmp)/bytearraywriter.o \
	$(outtmp)/filenotfoundexception.o \
	$(outtmp)/stringreader.o \
	$(outtmp)/byteringarrayreader.o \

filenotfoundexception :$(ioDir)/FileNotFoundException.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/FileNotFoundException.cpp -o $(outtmp)/filenotfoundexception.o $(external)

file :$(ioDir)/File.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/File.cpp -o $(outtmp)/file.o $(external)

fileinputstream :$(ioDir)/FileInputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/FileInputStream.cpp -o $(outtmp)/fileinputstream.o $(external)

libraryfileinputstream :$(ioDir)/LibraryFileInputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/LibraryFileInputStream.cpp -o $(outtmp)/libraryfileinputstream.o $(external)

inputstream :$(ioDir)/InputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/InputStream.cpp -o $(outtmp)/inputstream.o $(external)

fileoutputstream :$(ioDir)/FileOutputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/FileOutputStream.cpp -o $(outtmp)/fileoutputstream.o $(external)

outputstream :$(ioDir)/OutputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/OutputStream.cpp -o $(outtmp)/outputstream.o $(external)

printstream :$(ioDir)/PrintStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/PrintStream.cpp -o $(outtmp)/printstream.o $(external)

zipfilestream :$(ioDir)/ZipFileStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/ZipFileStream.cpp -o $(outtmp)/zipfilestream.o $(external)

zipmemorystream :$(ioDir)/ZipMemoryStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/ZipMemoryStream.cpp -o $(outtmp)/zipmemorystream.o $(external)

filewatcher :$(ioDir)/FileWatcher.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/FileWatcher.cpp -o $(outtmp)/filewatcher.o $(external)	

memoryfileinputstream :$(ioDir)/MemoryFileInputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/MemoryFileInputStream.cpp -o $(outtmp)/memoryfileinputstream.o $(external)

memoryfileoutputstream :$(ioDir)/MemoryFileOutputStream.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/MemoryFileOutputStream.cpp -o $(outtmp)/memoryfileoutputstream.o $(external)

filenodereader :$(ioDir)/FileNodeReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/FileNodeReader.cpp -o $(outtmp)/filenodereader.o $(external)

epollfileobserver :$(ioDir)/EPollFileObserver.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/EPollFileObserver.cpp -o $(outtmp)/epollfileobserver.o $(external)

bytearrayreader :$(ioDir)/ByteArrayReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/ByteArrayReader.cpp -o $(outtmp)/bytearrayreader.o $(external)	

bytearraywriter :$(ioDir)/ByteArrayWriter.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/ByteArrayWriter.cpp -o $(outtmp)/bytearraywriter.o $(external)		

stringreader :$(ioDir)/StringReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/StringReader.cpp -o $(outtmp)/stringreader.o $(external)		

byteringarrayreader :$(ioDir)/ByteRingArrayReader.cpp
	$(cppcompiler) $(obotchacppflags) -c $(ioDir)/ByteRingArrayReader.cpp -o $(outtmp)/byteringarrayreader.o $(external)		