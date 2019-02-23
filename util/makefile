outlib = ../out/lib
outtmp = ../out/tmp

gcc = g++

cflags = -fpic  -I ./concurrent/include/ -I ../lang/include -I ./include

external = -lpthread \
          -L ../out/lib/

objs =
link =
libname	= oboutil

everything : $(libname)

include ./concurrent/makefile

$(libname): $(link)
	g++ -g -shared $(objs) $(cflags) -o $(outlib)/lib${libname}.so $(external)
