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

obotchacppflags = $(cppflags) \
                $(obotchastrict)

external = -lpthread \
		-ldl \

sharelib = 	-L./out/lib/libssl.so \
			-L./out/lib/libcrypto.so \

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
	${shell cp ./external/openssl/libcrypto.so ./out/lib/libcrypto.so.3}
	${shell cp ./external/openssl/libssl.so ./out/lib/libssl.so.3}
	${shell ln -s libcrypto.so.3 ./out/lib/libcrypto.so}
	${shell ln -s libssl.so.3 ./out/lib/libssl.so}
	g++ -g -o0 -shared $(objs) $(cflags) $(sharelib) -o $(outlib)/lib${libname}.so $(external)
