sqlDir = ./sql

objs += $(outtmp)/sqlite3Client.o \
		$(outtmp)/mysqlClient.o \
		$(outtmp)/sqlquery.o \
		$(outtmp)/sqlrecords.o \
		$(outtmp)/sqlconnection.o \
		$(outtmp)/redisclient.o \
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

$(outtmp)/sqlite3Client.o :$(sqlDir)/sqlite3/Sqlite3Client.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3Client.cpp -o $(outtmp)/sqlite3Client.o

$(outtmp)/mysqlClient.o :$(sqlDir)/mysql/MySqlClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlClient.cpp -o $(outtmp)/mysqlClient.o

$(outtmp)/sqlquery.o :$(sqlDir)/SqlQuery.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlQuery.cpp -o $(outtmp)/sqlquery.o

$(outtmp)/sqlrecords.o :$(sqlDir)/SqlRecords.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlRecords.cpp -o $(outtmp)/sqlrecords.o

$(outtmp)/redisclient.o :$(sqlDir)/redis/RedisClient.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/redis/RedisClient.cpp -o $(outtmp)/redisclient.o