libmysqlext = ./external/mysql_connector/extlib


objs += $(outtmp)/mysql_ext_dbug_dbug.o \
		$(outtmp)/mysql_ext_dbug_analyze.o \
		$(outtmp)/mysql_ext_dbug_factorial.o \
		$(outtmp)/mysql_ext_dbug_sanity.o \
		

$(outtmp)/mysql_ext_dbug_dbug.o :$(libmysqlext)/dbug/dbug.c
	$(ccompiler) $(cflags) $(mysql_build_flag) -c $(libmysqlext)/dbug/dbug.c -o $(outtmp)/mysql_ext_dbug_dbug.o

$(outtmp)/mysql_ext_dbug_analyze.o :$(libmysqlext)/dbug/dbug_analyze.c
	$(ccompiler) $(cflags) $(mysql_build_flag) -c $(libmysqlext)/dbug/dbug_analyze.c -o $(outtmp)/mysql_ext_dbug_analyze.o

$(outtmp)/mysql_ext_dbug_factorial.o :$(libmysqlext)/dbug/factorial.c
	$(ccompiler) $(cflags) $(mysql_build_flag) -c $(libmysqlext)/dbug/factorial.c -o $(outtmp)/mysql_ext_dbug_factorial.o

$(outtmp)/mysql_ext_dbug_sanity.o :$(libmysqlext)/dbug/sanity.c
	$(ccompiler) $(cflags) $(mysql_build_flag) -c $(libmysqlext)/dbug/sanity.c -o $(outtmp)/mysql_ext_dbug_sanity.o

