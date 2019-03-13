langDir = lang

link += integer \
	boolean \
	double \
	float \
	system \
	string \
	long

objs += $(outtmp)/integer.o \
	$(outtmp)/boolean.o \
	$(outtmp)/double.o \
	$(outtmp)/float.o \
	$(outtmp)/system.o \
	$(outtmp)/string.o \
	$(outtmp)/long.o \

integer :$(langDir)/Integer.cpp
	$(gcc) $(cflags) -c $(langDir)/Integer.cpp -o $(outtmp)/integer.o $(external)

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
