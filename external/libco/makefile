libcocpp = ./external/libco

link += external_libco_coctx \
		external_libco_coctx_swap \
		external_libco_co_epoll \
		external_libco_co_hook_sys_call \
		external_libco_co_routine


objs += $(outtmp)/libcococtx.o \
		$(outtmp)/libcococtxswap.o \
		$(outtmp)/libcocoepoll.o \
		$(outtmp)/libcocohooksyscall.o \
		$(outtmp)/libcocoroutine.o \

external_libco_coctx :$(libcocpp)/coctx.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/coctx.cpp -o $(outtmp)/libcococtx.o

external_libco_coctx_swap :$(libcocpp)/coctx_swap.S
	cc $(cflags) -c $(libcocpp)/coctx_swap.S -o $(outtmp)/libcococtxswap.o

external_libco_co_epoll :$(libcocpp)/co_epoll.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_epoll.cpp -o $(outtmp)/libcocoepoll.o

external_libco_co_hook_sys_call :$(libcocpp)/co_hook_sys_call.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_hook_sys_call.cpp -o $(outtmp)/libcocohooksyscall.o

external_libco_co_routine :$(libcocpp)/co_routine.cpp
	$(cppcompiler) $(cppflags) -c $(libcocpp)/co_routine.cpp -o $(outtmp)/libcocoroutine.o

