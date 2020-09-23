libuuid = ./external/uuid

libuuid_flags = -I $(libuuid)/include \
                -DHAVE_CONFIG_H

objs += $(outtmp)/uuid_clear.o \
		$(outtmp)/uuid_compare.o \
		$(outtmp)/uuid_copy.o \
		$(outtmp)/uuid_gen_uuid.o \
		$(outtmp)/uuid_isnull.o \
		$(outtmp)/uuid_pack.o \
		$(outtmp)/uuid_parse.o \
		$(outtmp)/uuid_randutils.o \
		$(outtmp)/uuid_unpack.o \
		$(outtmp)/uuid_unparse.o \
		$(outtmp)/uuid_time.o \

$(outtmp)/uuid_clear.o :$(libuuid)/clear.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/clear.c -o $(outtmp)/uuid_clear.o

$(outtmp)/uuid_compare.o :$(libuuid)/compare.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/compare.c -o $(outtmp)/uuid_compare.o

$(outtmp)/uuid_gen_uuid.o :$(libuuid)/gen_uuid.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/gen_uuid.c -o $(outtmp)/uuid_gen_uuid.o

$(outtmp)/uuid_copy.o :$(libuuid)/copy.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/copy.c -o $(outtmp)/uuid_copy.o

$(outtmp)/uuid_isnull.o :$(libuuid)/isnull.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/isnull.c -o $(outtmp)/uuid_isnull.o

$(outtmp)/uuid_pack.o :$(libuuid)/pack.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/pack.c -o $(outtmp)/uuid_pack.o

$(outtmp)/uuid_parse.o :$(libuuid)/parse.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/parse.c -o $(outtmp)/uuid_parse.o

$(outtmp)/uuid_randutils.o :$(libuuid)/randutils.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/randutils.c -o $(outtmp)/uuid_randutils.o

$(outtmp)/uuid_unpack.o :$(libuuid)/unpack.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/unpack.c -o $(outtmp)/uuid_unpack.o

$(outtmp)/uuid_unparse.o :$(libuuid)/unparse.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/unparse.c -o $(outtmp)/uuid_unparse.o

$(outtmp)/uuid_time.o :$(libuuid)/uuid_time.c
		$(ccompiler) $(cflags) $(libuuid_flags) -c $(libuuid)/uuid_time.c -o $(outtmp)/uuid_time.o
