sqlDir = ./sql

objs += $(outtmp)/sqlite3connection.o \
		$(outtmp)/mysqlconnection.o \
		$(outtmp)/sqlquery.o \
		$(outtmp)/sqlrecords.o \
		$(outtmp)/sqlconnection.o \
		$(outtmp)/redisconnection.o \
		$(outtmp)/mysqlconnectparam.o \
		$(outtmp)/sqlite3connectparam.o \
		$(outtmp)/sqlconnectparam.o \
		
		
$(outtmp)/sqlconnectparam.o :$(sqlDir)/SqlConnectParam.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlConnectParam.cpp -o $(outtmp)/sqlconnectparam.o

$(outtmp)/sqlite3connectparam.o :$(sqlDir)/sqlite3/Sqlite3ConnectParam.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3ConnectParam.cpp -o $(outtmp)/sqlite3connectparam.o

$(outtmp)/mysqlconnectparam.o :$(sqlDir)/mysql/MySqlConnectParam.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlConnectParam.cpp -o $(outtmp)/mysqlconnectparam.o

$(outtmp)/sqlconnection.o :$(sqlDir)/SqlConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlConnection.cpp -o $(outtmp)/sqlconnection.o

$(outtmp)/sqlite3connection.o :$(sqlDir)/sqlite3/Sqlite3Connection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3Connection.cpp -o $(outtmp)/sqlite3connection.o

$(outtmp)/mysqlconnection.o :$(sqlDir)/mysql/MySqlConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlConnection.cpp -o $(outtmp)/mysqlconnection.o

$(outtmp)/sqlquery.o :$(sqlDir)/SqlQuery.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlQuery.cpp -o $(outtmp)/sqlquery.o

$(outtmp)/sqlrecords.o :$(sqlDir)/SqlRecords.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlRecords.cpp -o $(outtmp)/sqlrecords.o

$(outtmp)/redisconnection.o :$(sqlDir)/redis/RedisConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/redis/RedisConnection.cpp -o $(outtmp)/redisconnection.o