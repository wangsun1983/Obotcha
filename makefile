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
		-I ./security/include \
		-I ./external/iniparser/include \
		-I ./external/jsoncpp/include \
		-I ./external/rapidxml/include \
		-I ./external/zlib/include \
		-I ./external/ccl/include \
		-I ./external/yaml/include \
		-I ./external/crc32/include \
		-I ./external/md5/include \
		-I ./external/des/include \
		-g \


external = -lpthread \
		-L ../out/lib/

objs =
link =
libname = obotcha

everything : $(libname)

include external/makefile
include lang/makefile
include util/makefile
include io/makefile
include net/makefile
include security/makefile

$(libname): $(link)
	g++ -g -o0 -shared $(objs) $(cflags) -o $(outlib)/lib${libname}.so $(external)
