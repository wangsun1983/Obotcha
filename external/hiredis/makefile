hiredis = ./external/hiredis

hredis_include += -I $(confparser)/include \

objs += $(outtmp)/hiredis_alloc.o \
        $(outtmp)/hiredis_async.o \
        $(outtmp)/hiredis_dict.o \
        $(outtmp)/hiredis_hiredis.o \
        $(outtmp)/hiredis_net.o \
        $(outtmp)/hiredis_read.o \
		$(outtmp)/hiredis_sds.o \
		$(outtmp)/hiredis_sockcompat.o \
		$(outtmp)/hiredis_ssl.o \

$(outtmp)/hiredis_alloc.o :$(hiredis)/alloc.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/alloc.c -o $(outtmp)/hiredis_alloc.o

$(outtmp)/hiredis_async.o :$(hiredis)/async.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/async.c -o $(outtmp)/hiredis_async.o

$(outtmp)/hiredis_dict.o :$(hiredis)/dict.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/dict.c -o $(outtmp)/hiredis_dict.o

$(outtmp)/hiredis_hiredis.o :$(hiredis)/hiredis.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/hiredis.c -o $(outtmp)/hiredis_hiredis.o

$(outtmp)/hiredis_net.o :$(hiredis)/net.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/net.c -o $(outtmp)/hiredis_net.o

$(outtmp)/hiredis_read.o :$(hiredis)/read.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/read.c -o $(outtmp)/hiredis_read.o

$(outtmp)/hiredis_sds.o :$(hiredis)/sds.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/sds.c -o $(outtmp)/hiredis_sds.o

$(outtmp)/hiredis_sockcompat.o :$(hiredis)/sockcompat.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/sockcompat.c -o $(outtmp)/hiredis_sockcompat.o

$(outtmp)/hiredis_ssl.o :$(hiredis)/ssl.c
	$(ccompiler) $(cflags) $(ccl_include) -c $(hiredis)/ssl.c -o $(outtmp)/hiredis_ssl.o
