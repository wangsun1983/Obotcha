ioDir = io

link += file \
	fileinputstream \
	inputstream \
	outputstream \
	fileoutputstream \
	printstream \
	zipstream \
	filewatcher \
	memoryfile \
	memoryfileinputstream \
	memoryfileoutputstream \


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

file :$(ioDir)/File.cpp
	$(gcc) $(cflags) -c $(ioDir)/File.cpp -o $(outtmp)/file.o $(external)

fileinputstream :$(ioDir)/FileInputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/FileInputStream.cpp -o $(outtmp)/fileinputstream.o $(external)

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

memoryfile :$(ioDir)/MemoryFile.cpp
	$(gcc) $(cflags) -c $(ioDir)/MemoryFile.cpp -o $(outtmp)/memoryfile.o $(external)

memoryfileinputstream :$(ioDir)/MemoryFileInputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/MemoryFileInputStream.cpp -o $(outtmp)/memoryfileinputstream.o $(external)

memoryfileoutputstream :$(ioDir)/MemoryFileOutputStream.cpp
	$(gcc) $(cflags) -c $(ioDir)/MemoryFileOutputStream.cpp -o $(outtmp)/memoryfileoutputstream.o $(external)
