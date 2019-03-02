outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++ -std=c++11

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/ -I ../../io/include/ -I ../../util/include/

external = -lpthread \
           ../../out/lib/libobotcha.so \

files =
link =
libname	= mutextest

everything : $(libname)

$(libname): $(link)
	$(gcc) -O0 -g *.cpp $(cflags)  -o mytest
