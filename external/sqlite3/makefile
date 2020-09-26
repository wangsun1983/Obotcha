sqlite3 = ./external/sqlite3/src

objs += $(outtmp)/extsqlite3.o \

$(outtmp)/extsqlite3.o :$(sqlite3)/sqlite3.c
	$(ccompiler) $(cflags) -c $(sqlite3)/sqlite3.c -o $(outtmp)/extsqlite3.o
