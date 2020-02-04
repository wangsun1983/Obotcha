sqlite3 = ./external/sqlite3/src

link += external_sqlite3 \

objs += $(outtmp)/extsqlite3.o \

external_sqlite3 :$(sqlite3)/sqlite3.c
	$(ccompiler) $(cflags) $(zlib_flags) -c $(sqlite3)/sqlite3.c -o $(outtmp)/extsqlite3.o
