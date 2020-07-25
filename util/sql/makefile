sqlDir = ./util/sql

objs += $(outtmp)/sqlite3connection.o \
		$(outtmp)/sqlconnectionfactory.o \
		$(outtmp)/mysqlconnection.o \

$(outtmp)/sqlite3connection.o :$(sqlDir)/sqlite3/Sqlite3Connection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3Connection.cpp -o $(outtmp)/sqlite3connection.o

$(outtmp)/mysqlconnection.o :$(sqlDir)/mysql/MySqlConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlConnection.cpp -o $(outtmp)/mysqlconnection.o

$(outtmp)/sqlconnectionfactory.o :$(sqlDir)/SqlConnectionFactory.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlConnectionFactory.cpp -o $(outtmp)/sqlconnectionfactory.o
