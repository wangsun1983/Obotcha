ioDir = io

link += file \
	fileinputstream \
	inputstream \
	outputstream \
	fileoutputstream \
	printstream \
	zipstream \
	filewatcher \
	memoryfileinputstream \
	memoryfileoutputstream \
	libraryfileinputstream \
	filenodereader \
	epollfileobserver \
	bytearrayreader \
	bytearraywriter \
	filenotfoundexception \


objs += $(outtmp)/file.o \
	$(outtmp)/fileinputstream.o \
	$(outtmp)/inputstream.o \
	$(outtmp)/outputstream.o \
	$(outtmp)/fileoutputstream.o \
	$(outtmp)/printstream.o \
	$(outtmp)/zipstream.o \
	$(outtmp)/filewatcher.o \
	$(outtmp)/memoryfile.o \
	$(outtmp)/memoryfileinputstream.o \
	$(outtmp)/memoryfileoutputstream.o \
	$(outtmp)/libraryfileinputstream.o \
	$(outtmp)/filenodereader.o \
	$(outtmp)/epollfileobserver.o \
	$(outtmp)/bytearrayreader.o \
	$(outtmp)/bytearraywriter.o \
	$(outtmp)/filenotfoundexception.o \

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

zipstream :$(ioDir)/ZipStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/ZipStream.cpp -o $(outtmp)/zipstream.o $(external)

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