outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/ -I ../../io/include/ -I ../../util/include/ -I ../../net/include/

external = -lpthread \
           ../../out/lib/libobotcha.so \


files =
link =
libname	= arrayListTest

everything : $(libname)

$(libname): $(link)
	g++ -g *.cpp $(cflags)  $(external) -o mytest
