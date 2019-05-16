outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -fpic \
		-lrt \
		-I ../../util/concurrent/include/ \
		-I ../../util/coroutine/include/ \
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
		-I ../../external/ccl/include \
		-I ../../external/yaml/include \
		-I ../../external/crc32/include \
		-I ../../external/openssl/include \
		-I ../../external/libco \
		-g \

external = -lpthread \
           ../../out/lib/libobotcha.so \

files =
link =
libname	= integerTest

everything : $(libname)

$(libname): $(link)
	g++ *.cpp $(cflags) $(external) -o mytest
