outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -fpic \
		-lrt \
		-I ../../util/concurrent/include/ \
		-I ../../util/coroutine/include/ \
		-I ../../external/mysql_connector/include/ \
		-I ../../sql/include/ \
		-I ../../util/text/include/ \
		-I ../../lang/include \
		-I ../../io/include \
		-I ../../util/include/ \
		-I ../../net/include \
		-I ../../security/include \
		-I ../../process/include \
		-I ../../external/iniparser/include \
		-I ../../external/jsoncpp/include \
		-I ../../external/rapidxml/include \
		-I ../../external/zlib/include \
		-I ../../external/http_parser/include \
		-I ../../external/ccl/include \
		-I ../../external/yaml/include \
		-I ../../external/crc32/include \
		-I ../../external/openssl/include \
		-I ../../external/sqlite3/include \
		-I ../../external/libco \
		-O0 \
		-g \
		-std=c++17 \

external = -lpthread \
				-ldl \
				../../out/lib/libobotcha.so \

sharelib = -Wl,-rpath=../../out/lib/ \
           -L ../../out/lib/ \
           -lcrypto \
           -L ../../out/lib/ \
           -lssl \

files =
link =
libname	= test

everything : $(libname)

$(libname): $(link)
	g++ *.cpp $(cflags) -o mytest $(external) $(sharelib)
