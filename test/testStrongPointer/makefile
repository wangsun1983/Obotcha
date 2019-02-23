outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++ -std=c++11

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/

external = -lpthread \
           ../../out/lib/liboboutil.so \
					 ../../out/lib/libobolang.so \

files =
link =
libname	= mutextest

everything : $(libname)

$(libname): $(link)
	$(gcc) -O0 -g *.cpp $(cflags)  -o mytest
