crc32src = ./external/crc32

crc32flags = -msse4.1 \
			-msse2 \
			-msse3 \
			-msse4.2

link += external_crc32_crc32 \
		external_crc32_portal \
		external_crc32_sse42 \

objs += $(outtmp)/extcrc32crc.o \
        $(outtmp)/extcrc32portal.o \
        $(outtmp)/extcrc32sse42.o \

external_crc32_crc32 :$(crc32src)/src/crc32c.cc
	$(gcc) $(cflags) -c $(crc32src)/src/crc32c.cc -o $(outtmp)/extcrc32crc.o

external_crc32_portal :$(crc32src)/src/crc32c_portable.cc
	$(gcc) $(cflags) -c $(crc32src)/src/crc32c_portable.cc -o $(outtmp)/extcrc32portal.o

external_crc32_sse42 :$(crc32src)/src/crc32c_sse42.cc
	$(gcc) $(cflags) $(crc32flags) -c $(crc32src)/src/crc32c_sse42.cc -o $(outtmp)/extcrc32sse42.o