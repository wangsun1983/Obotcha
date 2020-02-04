sqlDir = ./util/sql

link += sqlite3connection \
		mysqlconnection \
		sqlconnectionfactory \

objs += $(outtmp)/sqlite3connection.o \
		$(outtmp)/mysqlconnection.o \
		$(outtmp)/sqlconnectionfactory.o \

sqlite3connection :$(sqlDir)/sqlite3/Sqlite3Connection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/sqlite3/Sqlite3Connection.cpp -o $(outtmp)/sqlite3connection.o

mysqlconnection :$(sqlDir)/mysql/MySqlConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/mysql/MySqlConnection.cpp -o $(outtmp)/mysqlconnection.o

sqlconnectionfactory :$(sqlDir)/SqlConnectionFactory.cpp
	$(cppcompiler) $(obotchacppflags) -c $(sqlDir)/SqlConnectionFactory.cpp -o $(outtmp)/sqlconnectionfactory.o	