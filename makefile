outlib = ./out/lib
outtmp = ./out/tmp

#gcc = g++
ccompiler = gcc
cppcompiler = g++

cflags = -fpic \
		-lrt \
		-I ./util/concurrent/include/ \
		-I ./util/coroutine/include/ \
		-I ./util/text/include/ \
		-I ./util/sql/include/ \
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
		-I ./external/openssl/include \
		-I ./external/sqlite3/include \
		-I ./external/http_parser/include \
		-I ./external/libco \
		-g \
		-rdynamic \
		-Wno-deprecated \

cppflags=$(cflags) \
		 -std=c++11

#define strict mode
#STRICT_MODE = yes

ifdef STRICT_MODE
obotchastrict = -Wall \
				-Werror \
				-Wextra
endif				

#define obotcha build config
obotchacflags = $(cflags) \
				$(obotchastrict)

obotchacppflags = $(obotchacflags)

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
