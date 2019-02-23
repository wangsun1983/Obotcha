outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/

external = -lpthread \
           ../../out/lib/liboboutil.so \
					 ../../out/lib/libobolang.so \

files =
link =
libname	= testBlockingQueue

everything : $(libname)

$(libname): $(link)
	g++ *.cpp $(cflags)  $(external) -o mytest
