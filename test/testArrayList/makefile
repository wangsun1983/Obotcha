outlib = ../../out/lib
outtmp = ../../out/tmp

gcc = g++

cflags = -I ../../util/concurrent/include/ -I ../../lang/include/ -I ../../util/include

external = -lpthread \
           ../../out/lib/liboboutil.so \
					 ../../out/lib/libobolang.so \

files =
link =
libname	= arrayListTest

everything : $(libname)

$(libname): $(link)
	g++ -g *.cpp $(cflags)  $(external) -o mytest
