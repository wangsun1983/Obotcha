ioDir = io

link += file \
	fileinputstream \
	inputstream \
	outputstream \
	fileoutputstream \


objs += $(outtmp)/file.o \
	$(outtmp)/fileinputstream.o \
	$(outtmp)/inputstream.o \
	$(outtmp)/outputstream.o \
	$(outtmp)/fileoutputstream.o \


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
