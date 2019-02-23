outlib = ../out/lib
outtmp = ../out/tmp
gcc = g++

libname = obolang

link = integer \
       boolean \
			 double \
			 float \
			 system \
			 string

objs = $(outtmp)/integer.o \
       $(outtmp)/boolean.o \
			 $(outtmp)/double.o \
			 $(outtmp)/float.o \
			 $(outtmp)/system.o \
			 $(outtmp)/string.o

cflags = -fpic -I ./include

everything : $(libname)

integer :Integer.cpp
	$(gcc) $(cflags) -c Integer.cpp -o $(outtmp)/integer.o $(external)

boolean :Boolean.cpp
	$(gcc) $(cflags) -c Boolean.cpp -o $(outtmp)/boolean.o $(external)

double :Double.cpp
	$(gcc) $(cflags) -c Double.cpp -o $(outtmp)/double.o $(external)

float :Float.cpp
	$(gcc) $(cflags) -c Float.cpp -o $(outtmp)/float.o $(external)

system :System.cpp
		$(gcc) $(cflags) -c System.cpp -o $(outtmp)/system.o $(external)

string :String.cpp
		$(gcc) $(cflags) -c String.cpp -o $(outtmp)/string.o $(external)

$(libname): $(link)
		g++ -shared $(objs) $(cflags) -o $(outlib)/lib${libname}.so $(external)
