outlib = ./out/lib
outtmp = ./out/tmp

gcc = g++

cflags = -fpic \
		-I ./util/concurrent/include/ \
		-I ./util/text/include/ \
		-I ./lang/include \
		-I ./io/include \
		-I ./util/include/ \
		-I ./net/include \


external = -lpthread \
		-L ../out/lib/

objs =
link =
libname = obotcha

everything : $(libname)

include lang/makefile
include util/makefile
include io/makefile
include net/makefile
include external/makefile

$(libname): $(link)
	g++ -g -o0 -shared $(objs) $(cflags) -o $(outlib)/lib${libname}.so $(external)
