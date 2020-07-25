libcocpp = ./external/libco

objs += $(outtmp)/libcococtx.o \
		$(outtmp)/libcococtxswap.o \
		$(outtmp)/libcocoepoll.o \
		$(outtmp)/libcocohooksyscall.o \
		$(outtmp)/libcocoroutine.o \

$(outtmp)/libcococtx.o :$(libcocpp)/coctx.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/coctx.cpp -o $(outtmp)/libcococtx.o

$(outtmp)/libcococtxswap.o :$(libcocpp)/coctx_swap.S
	cc $(cflags) -c $(libcocpp)/coctx_swap.S -o $(outtmp)/libcococtxswap.o

$(outtmp)/libcocoepoll.o :$(libcocpp)/co_epoll.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_epoll.cpp -o $(outtmp)/libcocoepoll.o

$(outtmp)/libcocohooksyscall.o :$(libcocpp)/co_hook_sys_call.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_hook_sys_call.cpp -o $(outtmp)/libcocohooksyscall.o

$(outtmp)/libcocoroutine.o :$(libcocpp)/co_routine.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_routine.cpp -o $(outtmp)/libcocoroutine.o
