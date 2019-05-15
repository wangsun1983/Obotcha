outlib = ./out/lib
outtmp = ./out/tmp

gcc = g++

cflags = -fpic \
		-lrt \
		-I ./util/concurrent/include/ \
		-I ./util/text/include/ \
		-I ./lang/include \
		-I ./io/include \
		-I ./util/include/ \
		-I ./net/include \
		-I ./security/include \
		-I ./process/include \
		-I ./external/iniparser/include \
		-I ./external/jsoncpp/include \
		-I ./external/rapidxml/include \
		-I ./external/zlib/include \
		-I ./external/ccl/include \
		-I ./external/yaml/include \
		-I ./external/crc32/include \
		-I ./external/openssl/include \
		-g \


external = -lpthread \
		-ldl \
		-L ../out/lib/ \

staticlib = ./external/openssl/libcrypto.a \
			./external/openssl/libssl.a \

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
include process/makefile

$(libname): $(link)
#	cd external/openssl/ && make
	g++ -g -o0 -shared $(objs) $(cflags) -o $(outlib)/lib${libname}.so $(staticlib) $(external)
