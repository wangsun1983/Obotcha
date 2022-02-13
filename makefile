outlib = ./out/lib
outtmp = ./out/tmp

#gcc = g++
ccompiler = clang
cppcompiler = clang++
clangcompiler = clang++


cflags = -fpic \
		-I ./util/concurrent/include/ \
		-I ./util/coroutine/include/ \
		-I ./util/text/include/ \
		-I ./sql/include/ \
		-I ./lang/include \
		-I ./io/include \
		-I ./util/include/ \
		-I ./net/include \
		-I ./net/http/client/include \
		-I ./security/include \
		-I ./process/include \
		-I ./external/iniparser/include \
		-I ./external/glog/include \
		-I ./external/jsoncpp/include \
		-I ./external/rapidxml/include \
		-I ./external/zlib/include \
		-I ./external/ccl/include \
		-I ./external/yaml/include \
		-I ./external/openssl/include \
		-I ./external/sqlite3/include \
		-I ./external/libco \
		-I ./external/mysql_connector/include \
		-I ./external/uuid/include \
		-I ./external/hiredis/include \
		-Wno-deprecated \
		-g \

cppflags=$(cflags) \
		 -std=c++14 \
		 -fsanitize=address \
		 -fno-omit-frame-pointer

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
		-pthread \
		-ldl \
		-lrt \
		-rdynamic

#sharelib = 	-L./out/lib/libssl.so \
#			-L./out/lib/libcrypto.so \

staticlib = ./out/lib/libssl.a \
		./out/lib/libcrypto.a \

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
include sql/makefile

$(libname): $(objs)
	g++ -g -o0 -shared $(objs) $(cflags) $(sharelib) -o $(outlib)/lib${libname}.so $(staticlib) $(external)

#$(libname): $(objs)
#	g++ -os -shared $(objs) $(cflags) $(sharelib) -o $(outlib)/lib${libname}.so $(staticlib) $(external)
