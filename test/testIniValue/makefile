outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/ -I ../../io/include/ -I ../../util/include/ -I ../../net/include/ -I ../../util/text/include -I ../../external/iniparser/include/

external = -lpthread \
           ../../out/lib/libobotcha.so \


files =
link =
libname	= inetAddressTest

everything : $(libname)

$(libname): $(link)
	g++ -g -o0 *.cpp $(cflags)  $(external) -o mytest
