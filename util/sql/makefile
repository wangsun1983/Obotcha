sqlDir = ./util/sql

link += sqlite3connection \
		mysqlconnection \
		sqlconnectionfactory \

objs += $(outtmp)/sqlite3connection.o \
		$(outtmp)/mysqlconnection.o \
		$(outtmp)/sqlconnectionfactory.o \

sqlite3connection :$(sqlDir)/sqlite3/Sqlite3Connection.cpp
	$(gcc) $(cflags) -c $(sqlDir)/sqlite3/Sqlite3Connection.cpp -o $(outtmp)/sqlite3connection.o

mysqlconnection :$(sqlDir)/mysql/MySqlConnection.cpp
	$(gcc) $(cflags) -c $(sqlDir)/mysql/MySqlConnection.cpp -o $(outtmp)/mysqlconnection.o

sqlconnectionfactory :$(sqlDir)/SqlConnectionFactory.cpp
	$(gcc) $(cflags) -c $(sqlDir)/SqlConnectionFactory.cpp -o $(outtmp)/sqlconnectionfactory.o	