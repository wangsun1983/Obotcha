langDir = lang

objs += $(outtmp)/integer.o \
	$(outtmp)/boolean.o \
	$(outtmp)/double.o \
	$(outtmp)/field.o \
	$(outtmp)/float.o \
	$(outtmp)/system.o \
	$(outtmp)/string.o \
	$(outtmp)/long.o \
	$(outtmp)/bytearray.o \
	$(outtmp)/byteringarray.o \
	$(outtmp)/uint64.o \
	$(outtmp)/uint32.o \
	$(outtmp)/uint16.o \
	$(outtmp)/uint8.o \
	$(outtmp)/byte.o \
	$(outtmp)/exception.o \
	$(outtmp)/stringbuffer.o \

$(outtmp)/integer.o :$(langDir)/Integer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Integer.cpp -o $(outtmp)/integer.o 

$(outtmp)/field.o :$(langDir)/Field.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Field.cpp -o $(outtmp)/field.o 

$(outtmp)/uint64.o :$(langDir)/Uint64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint64.cpp -o $(outtmp)/uint64.o 

$(outtmp)/uint32.o :$(langDir)/Uint32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint32.cpp -o $(outtmp)/uint32.o 

$(outtmp)/uint16.o :$(langDir)/Uint16.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint16.cpp -o $(outtmp)/uint16.o 

$(outtmp)/uint8.o :$(langDir)/Uint8.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint8.cpp -o $(outtmp)/uint8.o 

$(outtmp)/boolean.o :$(langDir)/Boolean.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Boolean.cpp -o $(outtmp)/boolean.o 

$(outtmp)/double.o :$(langDir)/Double.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Double.cpp -o $(outtmp)/double.o 

$(outtmp)/float.o :$(langDir)/Float.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Float.cpp -o $(outtmp)/float.o 

$(outtmp)/system.o :$(langDir)/System.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/System.cpp -o $(outtmp)/system.o 

$(outtmp)/string.o :$(langDir)/String.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/String.cpp -o $(outtmp)/string.o 

$(outtmp)/stringbuffer.o :$(langDir)/StringBuffer.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/StringBuffer.cpp -o $(outtmp)/stringbuffer.o 

$(outtmp)/long.o :$(langDir)/Long.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Long.cpp -o $(outtmp)/long.o 

$(outtmp)/bytearray.o :$(langDir)/ByteArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteArray.cpp -o $(outtmp)/bytearray.o 

$(outtmp)/byteringarray.o :$(langDir)/ByteRingArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteRingArray.cpp -o $(outtmp)/byteringarray.o 

$(outtmp)/byte.o :$(langDir)/Byte.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Byte.cpp -o $(outtmp)/byte.o 

$(outtmp)/exception.o :$(langDir)/Exception.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Exception.cpp -o $(outtmp)/exception.o 
