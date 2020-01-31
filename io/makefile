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
	$(gcc) $(cflags) -c $(ioDir)/FileNotFoundException.cpp -o $(outtmp)/filenotfoundexception.o $(external)

file :$(ioDir)/File.cpp
	$(gcc) $(cflags) -c $(ioDir)/File.cpp -o $(outtmp)/file.o $(external)

fileinputstream :$(ioDir)/FileInputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/FileInputStream.cpp -o $(outtmp)/fileinputstream.o $(external)

libraryfileinputstream :$(ioDir)/LibraryFileInputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/LibraryFileInputStream.cpp -o $(outtmp)/libraryfileinputstream.o $(external)

inputstream :$(ioDir)/InputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/InputStream.cpp -o $(outtmp)/inputstream.o $(external)

fileoutputstream :$(ioDir)/FileOutputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/FileOutputStream.cpp -o $(outtmp)/fileoutputstream.o $(external)

outputstream :$(ioDir)/OutputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/OutputStream.cpp -o $(outtmp)/outputstream.o $(external)

printstream :$(ioDir)/PrintStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/PrintStream.cpp -o $(outtmp)/printstream.o $(external)

zipfilestream :$(ioDir)/ZipFileStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/ZipFileStream.cpp -o $(outtmp)/zipfilestream.o $(external)

zipmemorystream :$(ioDir)/ZipMemoryStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/ZipMemoryStream.cpp -o $(outtmp)/zipmemorystream.o $(external)

filewatcher :$(ioDir)/FileWatcher.cpp
	$(gcc) $(cflags) -c $(ioDir)/FileWatcher.cpp -o $(outtmp)/filewatcher.o $(external)	

memoryfileinputstream :$(ioDir)/MemoryFileInputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/MemoryFileInputStream.cpp -o $(outtmp)/memoryfileinputstream.o $(external)

memoryfileoutputstream :$(ioDir)/MemoryFileOutputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/MemoryFileOutputStream.cpp -o $(outtmp)/memoryfileoutputstream.o $(external)

filenodereader :$(ioDir)/FileNodeReader.cpp
	$(gcc) $(cflags) -c $(ioDir)/FileNodeReader.cpp -o $(outtmp)/filenodereader.o $(external)

epollfileobserver :$(ioDir)/EPollFileObserver.cpp
	$(gcc) $(cflags) -c $(ioDir)/EPollFileObserver.cpp -o $(outtmp)/epollfileobserver.o $(external)

bytearrayreader :$(ioDir)/ByteArrayReader.cpp
	$(gcc) $(cflags) -c $(ioDir)/ByteArrayReader.cpp -o $(outtmp)/bytearrayreader.o $(external)	

bytearraywriter :$(ioDir)/ByteArrayWriter.cpp
	$(gcc) $(cflags) -c $(ioDir)/ByteArrayWriter.cpp -o $(outtmp)/bytearraywriter.o $(external)		

stringreader :$(ioDir)/StringReader.cpp
	$(gcc) $(cflags) -c $(ioDir)/StringReader.cpp -o $(outtmp)/stringreader.o $(external)		

byteringarrayreader :$(ioDir)/ByteRingArrayReader.cpp
	$(gcc) $(cflags) -c $(ioDir)/ByteRingArrayReader.cpp -o $(outtmp)/byteringarrayreader.o $(external)		