langDir = lang

objs += $(outtmp)/integer.o \
	$(outtmp)/boolean.o \
	$(outtmp)/double.o \
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
  $(outtmp)/outofboundsexception.o \
	$(outtmp)/methodnotsupportexception.o \
	$(outtmp)/protocolnotsupportexception.o \
	$(outtmp)/nullpointerexception.o \
	$(outtmp)/initializeexception.o \
	$(outtmp)/error.o \
	$(outtmp)/valuenotfoundexception.o \
	$(outtmp)/transformexception.o \
	$(outtmp)/illegalstateexception.o \
	$(outtmp)/illegalargumentexception.o

$(outtmp)/integer.o :$(langDir)/Integer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Integer.cpp -o $(outtmp)/integer.o $(external)

$(outtmp)/uint64.o :$(langDir)/Uint64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint64.cpp -o $(outtmp)/uint64.o $(external)

$(outtmp)/uint32.o :$(langDir)/Uint32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint32.cpp -o $(outtmp)/uint32.o $(external)

$(outtmp)/uint16.o :$(langDir)/Uint16.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint16.cpp -o $(outtmp)/uint16.o $(external)

$(outtmp)/uint8.o :$(langDir)/Uint8.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint8.cpp -o $(outtmp)/uint8.o $(external)

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

$(outtmp)/long.o :$(langDir)/Long.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Long.cpp -o $(outtmp)/long.o $(external)

$(outtmp)/bytearray.o :$(langDir)/ByteArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteArray.cpp -o $(outtmp)/bytearray.o $(external)

$(outtmp)/byteringarray.o :$(langDir)/ByteRingArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteRingArray.cpp -o $(outtmp)/byteringarray.o $(external)

$(outtmp)/byte.o :$(langDir)/Byte.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Byte.cpp -o $(outtmp)/byte.o $(external)

$(outtmp)/exception.o :$(langDir)/Exception.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Exception.cpp -o $(outtmp)/exception.o $(external)

$(outtmp)/outofboundsexception.o :$(langDir)/ArrayIndexOutOfBoundsException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ArrayIndexOutOfBoundsException.cpp -o $(outtmp)/outofboundsexception.o $(external)

$(outtmp)/methodnotsupportexception.o :$(langDir)/MethodNotSupportException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/MethodNotSupportException.cpp -o $(outtmp)/methodnotsupportexception.o $(external)

$(outtmp)/initializeexception.o :$(langDir)/InitializeException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/InitializeException.cpp -o $(outtmp)/initializeexception.o $(external)

$(outtmp)/nullpointerexception.o :$(langDir)/NullPointerException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/NullPointerException.cpp -o $(outtmp)/nullpointerexception.o $(external)

$(outtmp)/protocolnotsupportexception.o :$(langDir)/ProtocolNotSupportException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ProtocolNotSupportException.cpp -o $(outtmp)/protocolnotsupportexception.o $(external)

$(outtmp)/error.o :$(langDir)/Error.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Error.cpp -o $(outtmp)/error.o $(external)

$(outtmp)/valuenotfoundexception.o :$(langDir)/ValueNotFoundException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ValueNotFoundException.cpp -o $(outtmp)/valuenotfoundexception.o $(external)

$(outtmp)/transformexception.o :$(langDir)/TransformException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/TransformException.cpp -o $(outtmp)/transformexception.o $(external)

$(outtmp)/illegalstateexception.o :$(langDir)/IllegalStateException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/IllegalStateException.cpp -o $(outtmp)/illegalstateexception.o $(external)

$(outtmp)/illegalargumentexception.o :$(langDir)/IllegalArgumentException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/IllegalArgumentException.cpp -o $(outtmp)/illegalargumentexception.o $(external)
