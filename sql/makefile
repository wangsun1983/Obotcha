sqlDir = ./sql

objs += $(outtmp)/sqlite3Client.o \
		$(outtmp)/mysqlClient.o \
		$(outtmp)/sqlquery.o \
		$(outtmp)/sqlrecords.o \
		

$(outtmp)/sqlite3Client.o :$(sqlDir)/sqlite3/Sqlite3Client.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3Client.cpp -o $(outtmp)/sqlite3Client.o

$(outtmp)/mysqlClient.o :$(sqlDir)/mysql/MySqlClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlClient.cpp -o $(outtmp)/mysqlClient.o

$(outtmp)/sqlquery.o :$(sqlDir)/SqlQuery.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlQuery.cpp -o $(outtmp)/sqlquery.o

$(outtmp)/sqlrecords.o :$(sqlDir)/SqlRecords.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlRecords.cpp -o $(outtmp)/sqlrecords.o