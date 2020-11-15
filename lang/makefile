langDir = lang

objs += $(outtmp)/boolean.o \
	$(outtmp)/double.o \
	$(outtmp)/field.o \
	$(outtmp)/float.o \
	$(outtmp)/system.o \
	$(outtmp)/string.o \
	$(outtmp)/bytearray.o \
	$(outtmp)/byteringarray.o \
	$(outtmp)/exception.o \
	$(outtmp)/error.o \

$(outtmp)/field.o :$(langDir)/Field.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Field.cpp -o $(outtmp)/field.o $(external)

$(outtmp)/boolean.o :$(langDir)/Boolean.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Boolean.cpp -o $(outtmp)/boolean.o $(external)

$(outtmp)/double.o :$(langDir)/Double.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Double.cpp -o $(outtmp)/double.o $(external)

$(outtmp)/float.o :$(langDir)/Float.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Float.cpp -o $(outtmp)/float.o $(external)

$(outtmp)/system.o :$(langDir)/System.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/System.cpp -o $(outtmp)/system.o $(external)

$(outtmp)/string.o :$(langDir)/String.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/String.cpp -o $(outtmp)/string.o $(external)

$(outtmp)/bytearray.o :$(langDir)/ByteArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteArray.cpp -o $(outtmp)/bytearray.o $(external)

$(outtmp)/byteringarray.o :$(langDir)/ByteRingArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteRingArray.cpp -o $(outtmp)/byteringarray.o $(external)

$(outtmp)/exception.o :$(langDir)/Exception.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Exception.cpp -o $(outtmp)/exception.o $(external)

$(outtmp)/error.o :$(langDir)/Error.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Error.cpp -o $(outtmp)/error.o $(external)
