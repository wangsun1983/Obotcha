zlib = ./external/zlib/src

zlib_flags = -Wall  \
			-DUSE_MMAP \
			-DZLIB_CONST \

link += external_zlib_adler32 \
		external_zlib_compress \
		external_zlib_crc32 \
		external_zlib_deflate \
		external_zlib_gzclose \
		external_zlib_gzlib \
		external_zlib_gzread \
		external_zlib_gzwrite \
		external_zlib_infback \
		external_zlib_inflate \
		external_zlib_inftrees \
		external_zlib_inffast \
		external_zlib_trees \
		external_zlib_uncompr \
		external_zlib_zutil \
		external_zlib_ioapi \
		external_zlib_miniunz \
		external_zlib_minizip \
		external_zlib_mztool\
		external_zlib_unzip \
		external_zlib_zip \

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

external_zlib_adler32 :$(zlib)/adler32.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/adler32.c -o $(outtmp)/extzlibadler32.o

external_zlib_compress :$(zlib)/compress.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/compress.c -o $(outtmp)/extzlibcompress.o

external_zlib_crc32 :$(zlib)/crc32.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/crc32.c -o $(outtmp)/extzlibcrc32.o

external_zlib_deflate :$(zlib)/deflate.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/deflate.c -o $(outtmp)/extzlibdeflate.o

external_zlib_gzclose :$(zlib)/gzclose.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/gzclose.c -o $(outtmp)/extzlibgzclose.o

external_zlib_gzlib :$(zlib)/gzlib.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/gzlib.c -o $(outtmp)/extzlibgzlib.o

external_zlib_gzread :$(zlib)/gzread.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/gzread.c -o $(outtmp)/extzlibgzread.o

external_zlib_gzwrite :$(zlib)/gzwrite.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/gzwrite.c -o $(outtmp)/extzlibgzwrite.o

external_zlib_infback :$(zlib)/infback.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/infback.c -o $(outtmp)/extzlibinfback.o

external_zlib_inflate :$(zlib)/inflate.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/inflate.c -o $(outtmp)/extzlibinflate.o

external_zlib_inftrees :$(zlib)/inftrees.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/inftrees.c -o $(outtmp)/extzlibinftrees.o

external_zlib_inffast :$(zlib)/inffast.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/inffast.c -o $(outtmp)/extzlibinffast.o

external_zlib_trees :$(zlib)/trees.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/trees.c -o $(outtmp)/extzlibtrees.o

external_zlib_uncompr :$(zlib)/uncompr.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/uncompr.c -o $(outtmp)/extzlibuncompr.o

external_zlib_zutil :$(zlib)/zutil.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/zutil.c -o $(outtmp)/extzlibzutil.o

external_zlib_crypt :$(zlib)/crypt.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/crypt.c -o $(outtmp)/extzlibcrypt.o

external_zlib_ioapi :$(zlib)/ioapi.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/ioapi.c -o $(outtmp)/extzlibioapi.o

external_zlib_mztool :$(zlib)/mztools.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/mztools.c -o $(outtmp)/extzlibmztool.o				

external_zlib_unzip :$(zlib)/unzip.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/unzip.c -o $(outtmp)/extzlibunzip.o

external_zlib_zip :$(zlib)/zip.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/zip.c -o $(outtmp)/extzlibzip.o

external_zlib_miniunz :$(zlib)/miniunz.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/miniunz.c -o $(outtmp)/extzlibminiunz.o

external_zlib_minizip :$(zlib)/minizip.c
	cc $(cflags) $(zlib_flags) -c $(zlib)/minizip.c -o $(outtmp)/extzlibminizip.o