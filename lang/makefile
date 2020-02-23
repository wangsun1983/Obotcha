langDir = lang

link += integer \
	boolean \
	double \
	float \
	system \
	string \
	long \
	bytearray \
	byteringarray \
	uint64 \
	uint32 \
	uint16 \
	uint8 \
	byte \
	exception \
	outofboundsexception\
	methodnotsupportexception \
	protocolnotsupportexception \
	nullpointerexception \
	initializeexception \
	valuenotfoundexception \
	transformexception \
	illegalstateexception \
	illegalargumentexception \
	error \

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

integer :$(langDir)/Integer.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Integer.cpp -o $(outtmp)/integer.o $(external)

uint64 :$(langDir)/Uint64.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint64.cpp -o $(outtmp)/uint64.o $(external)

uint32 :$(langDir)/Uint32.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint32.cpp -o $(outtmp)/uint32.o $(external)

uint16 :$(langDir)/Uint16.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint16.cpp -o $(outtmp)/uint16.o $(external)

uint8 :$(langDir)/Uint8.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Uint8.cpp -o $(outtmp)/uint8.o $(external)

boolean :$(langDir)/Boolean.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Boolean.cpp -o $(outtmp)/boolean.o $(external)

double :$(langDir)/Double.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Double.cpp -o $(outtmp)/double.o $(external)

float :$(langDir)/Float.cpp
	$(cppcompiler) $(obotchacppflags) -c $(langDir)/Float.cpp -o $(outtmp)/float.o $(external)

system :$(langDir)/System.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/System.cpp -o $(outtmp)/system.o $(external)

string :$(langDir)/String.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/String.cpp -o $(outtmp)/string.o $(external)

long :$(langDir)/Long.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Long.cpp -o $(outtmp)/long.o $(external)

bytearray :$(langDir)/ByteArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteArray.cpp -o $(outtmp)/bytearray.o $(external)

byteringarray :$(langDir)/ByteRingArray.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ByteRingArray.cpp -o $(outtmp)/byteringarray.o $(external)

byte :$(langDir)/Byte.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Byte.cpp -o $(outtmp)/byte.o $(external)

exception :$(langDir)/Exception.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Exception.cpp -o $(outtmp)/exception.o $(external)

outofboundsexception :$(langDir)/ArrayIndexOutOfBoundsException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ArrayIndexOutOfBoundsException.cpp -o $(outtmp)/outofboundsexception.o $(external)

methodnotsupportexception :$(langDir)/MethodNotSupportException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/MethodNotSupportException.cpp -o $(outtmp)/methodnotsupportexception.o $(external)

initializeexception :$(langDir)/InitializeException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/InitializeException.cpp -o $(outtmp)/initializeexception.o $(external)

nullpointerexception :$(langDir)/NullPointerException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/NullPointerException.cpp -o $(outtmp)/nullpointerexception.o $(external)

protocolnotsupportexception :$(langDir)/ProtocolNotSupportException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ProtocolNotSupportException.cpp -o $(outtmp)/protocolnotsupportexception.o $(external)

error :$(langDir)/Error.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/Error.cpp -o $(outtmp)/error.o $(external)

valuenotfoundexception :$(langDir)/ValueNotFoundException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/ValueNotFoundException.cpp -o $(outtmp)/valuenotfoundexception.o $(external)

transformexception :$(langDir)/TransformException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/TransformException.cpp -o $(outtmp)/transformexception.o $(external)

illegalstateexception :$(langDir)/IllegalStateException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/IllegalStateException.cpp -o $(outtmp)/illegalstateexception.o $(external)

illegalargumentexception :$(langDir)/IllegalArgumentException.cpp
		$(cppcompiler) $(obotchacppflags) -c $(langDir)/IllegalArgumentException.cpp -o $(outtmp)/illegalargumentexception.o $(external)
