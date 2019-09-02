langDir = lang

link += integer \
	boolean \
	double \
	float \
	system \
	string \
	long \
	bytearray \
	uint64 \
	uint32 \
	uint16 \
	uint8 \
	byte \
	exception \

objs += $(outtmp)/integer.o \
	$(outtmp)/boolean.o \
	$(outtmp)/double.o \
	$(outtmp)/float.o \
	$(outtmp)/system.o \
	$(outtmp)/string.o \
	$(outtmp)/long.o \
	$(outtmp)/bytearray.o \
	$(outtmp)/uint64.o \
	$(outtmp)/uint32.o \
	$(outtmp)/uint16.o \
	$(outtmp)/uint8.o \
	$(outtmp)/byte.o \
	$(outtmp)/exception.o \


integer :$(langDir)/Integer.cpp
	$(gcc) $(cflags) -c $(langDir)/Integer.cpp -o $(outtmp)/integer.o $(external)

uint64 :$(langDir)/Uint64.cpp
	$(gcc) $(cflags) -c $(langDir)/Uint64.cpp -o $(outtmp)/uint64.o $(external)

uint32 :$(langDir)/Uint32.cpp
	$(gcc) $(cflags) -c $(langDir)/Uint32.cpp -o $(outtmp)/uint32.o $(external)

uint16 :$(langDir)/Uint16.cpp
	$(gcc) $(cflags) -c $(langDir)/Uint16.cpp -o $(outtmp)/uint16.o $(external)

uint8 :$(langDir)/Uint8.cpp
	$(gcc) $(cflags) -c $(langDir)/Uint8.cpp -o $(outtmp)/uint8.o $(external)

boolean :$(langDir)/Boolean.cpp
	$(gcc) $(cflags) -c $(langDir)/Boolean.cpp -o $(outtmp)/boolean.o $(external)

double :$(langDir)/Double.cpp
	$(gcc) $(cflags) -c $(langDir)/Double.cpp -o $(outtmp)/double.o $(external)

float :$(langDir)/Float.cpp
	$(gcc) $(cflags) -c $(langDir)/Float.cpp -o $(outtmp)/float.o $(external)

system :$(langDir)/System.cpp
		$(gcc) $(cflags) -c $(langDir)/System.cpp -o $(outtmp)/system.o $(external)

string :$(langDir)/String.cpp
		$(gcc) $(cflags) -c $(langDir)/String.cpp -o $(outtmp)/string.o $(external)

long :$(langDir)/Long.cpp
		$(gcc) $(cflags) -c $(langDir)/Long.cpp -o $(outtmp)/long.o $(external)

bytearray :$(langDir)/ByteArray.cpp
		$(gcc) $(cflags) -c $(langDir)/ByteArray.cpp -o $(outtmp)/bytearray.o $(external)

byte :$(langDir)/Byte.cpp
		$(gcc) $(cflags) -c $(langDir)/Byte.cpp -o $(outtmp)/byte.o $(external)

exception :$(langDir)/Exception.cpp
		$(gcc) $(cflags) -c $(langDir)/Exception.cpp -o $(outtmp)/exception.o $(external)
