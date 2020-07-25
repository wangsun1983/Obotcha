zlib = ./external/zlib/src

zlib_flags = -Wall  \
			-DUSE_MMAP \
			-DZLIB_CONST \

objs += $(outtmp)/extzlibadler32.o \
		$(outtmp)/extzlibcompress.o \
		$(outtmp)/extzlibcrc32.o \
		$(outtmp)/extzlibdeflate.o \
		$(outtmp)/extzlibgzclose.o \
		$(outtmp)/extzlibgzlib.o \
		$(outtmp)/extzlibgzread.o \
		$(outtmp)/extzlibgzwrite.o \
		$(outtmp)/extzlibinfback.o \
		$(outtmp)/extzlibinflate.o \
		$(outtmp)/extzlibinftrees.o \
		$(outtmp)/extzlibinffast.o \
		$(outtmp)/extzlibtrees.o \
		$(outtmp)/extzlibuncompr.o \
		$(outtmp)/extzlibzutil.o \
		$(outtmp)/extzlibioapi.o \
		$(outtmp)/extzlibmztool.o \
		$(outtmp)/extzlibminizip.o \
		$(outtmp)/extzlibunzip.o \
		$(outtmp)/extzlibzip.o \

$(outtmp)/extzlibadler32.o :$(zlib)/adler32.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/adler32.c -o $(outtmp)/extzlibadler32.o

$(outtmp)/extzlibcompress.o :$(zlib)/compress.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/compress.c -o $(outtmp)/extzlibcompress.o

$(outtmp)/extzlibcrc32.o :$(zlib)/crc32.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/crc32.c -o $(outtmp)/extzlibcrc32.o

$(outtmp)/extzlibdeflate.o :$(zlib)/deflate.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/deflate.c -o $(outtmp)/extzlibdeflate.o

$(outtmp)/extzlibgzclose.o :$(zlib)/gzclose.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/gzclose.c -o $(outtmp)/extzlibgzclose.o

$(outtmp)/extzlibgzlib.o :$(zlib)/gzlib.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/gzlib.c -o $(outtmp)/extzlibgzlib.o

$(outtmp)/extzlibgzread.o :$(zlib)/gzread.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/gzread.c -o $(outtmp)/extzlibgzread.o

$(outtmp)/extzlibgzwrite.o :$(zlib)/gzwrite.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/gzwrite.c -o $(outtmp)/extzlibgzwrite.o

$(outtmp)/extzlibinfback.o :$(zlib)/infback.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/infback.c -o $(outtmp)/extzlibinfback.o

$(outtmp)/extzlibinflate.o :$(zlib)/inflate.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/inflate.c -o $(outtmp)/extzlibinflate.o

$(outtmp)/extzlibinftrees.o :$(zlib)/inftrees.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/inftrees.c -o $(outtmp)/extzlibinftrees.o

$(outtmp)/extzlibinffast.o :$(zlib)/inffast.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/inffast.c -o $(outtmp)/extzlibinffast.o

$(outtmp)/extzlibtrees.o :$(zlib)/trees.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/trees.c -o $(outtmp)/extzlibtrees.o

$(outtmp)/extzlibuncompr.o :$(zlib)/uncompr.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/uncompr.c -o $(outtmp)/extzlibuncompr.o

$(outtmp)/extzlibzutil.o :$(zlib)/zutil.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/zutil.c -o $(outtmp)/extzlibzutil.o

$(outtmp)/extzlibcrypt.o :$(zlib)/crypt.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/crypt.c -o $(outtmp)/extzlibcrypt.o

$(outtmp)/extzlibioapi.o :$(zlib)/ioapi.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/ioapi.c -o $(outtmp)/extzlibioapi.o

$(outtmp)/extzlibmztool.o :$(zlib)/mztools.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/mztools.c -o $(outtmp)/extzlibmztool.o

$(outtmp)/extzlibunzip.o :$(zlib)/unzip.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/unzip.c -o $(outtmp)/extzlibunzip.o

$(outtmp)/extzlibzip.o :$(zlib)/zip.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/zip.c -o $(outtmp)/extzlibzip.o

$(outtmp)/extzlibminiunz.o :$(zlib)/miniunz.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/miniunz.c -o $(outtmp)/extzlibminiunz.o

$(outtmp)/extzlibminizip.o :$(zlib)/minizip.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(zlib)/minizip.c -o $(outtmp)/extzlibminizip.o
