outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -fpic \
		-I ../../util/concurrent/include/ \
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
		-g \
		-std=c++11 \

external = -lpthread \
           ../../out/lib/libobotcha.so \

files =
link =
libname	= threadTest

everything : $(libname)

$(libname): $(link)
	g++ *.cpp $(cflags)  $(external) -o mytest
