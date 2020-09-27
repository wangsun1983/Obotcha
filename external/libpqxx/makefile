libpq = ./external/libpqxx

libpq_include += -I $(libpq)/include/pqxx \
				-I $(libpq)/include/ \
				-I $(libpq)/include/pqxx/internal \
				-I $(libpq)/include/postgresql \
				-I $(libpq)/config/sample-headers/compiler/gcc-7.2/pqxx \


objs += $(outtmp)/libpq_array.o \
		$(outtmp)/libpq_binarystring.o \
		$(outtmp)/libpq_connection.o \
		$(outtmp)/libpq_connection_base.o \
		$(outtmp)/libpq_cursor.o \
		$(outtmp)/libpq_dbtransaction.o \
		$(outtmp)/libpq_encodings.o \
		$(outtmp)/libpq_errorhandler.o \
		$(outtmp)/libpq_except.o \
		$(outtmp)/libpq_field.o \
		$(outtmp)/libpq_largeobject.o \
		$(outtmp)/libpq_nontransaction.o \
		$(outtmp)/libpq_notification.o \
		$(outtmp)/libpq_pipeline.o \
		$(outtmp)/libpq_prepared_statement.o \
		$(outtmp)/libpq_result.o \
		$(outtmp)/libpq_robusttransaction.o \
		$(outtmp)/libpq_row.o \
		$(outtmp)/libpq_sql_cursor.o \
		$(outtmp)/libpq_statement_parameters.o \
		$(outtmp)/libpq_strconv.o \
		$(outtmp)/libpq_stream_base.o \
		$(outtmp)/libpq_stream_from.o \
		$(outtmp)/libpq_stream_to.o \
		$(outtmp)/libpq_substransaction.o \
		$(outtmp)/libpq_tablereader.o \
		$(outtmp)/libpq_tablestream.o \
		$(outtmp)/libpq_tablewriter.o \
		$(outtmp)/libpq_transaction.o \
		$(outtmp)/libpq_transaction_base.o \
		$(outtmp)/libpq_util.o \
		$(outtmp)/libpq_version.o \


$(outtmp)/libpq_version.o :$(libpq)/src/version.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/version.cxx -o $(outtmp)/libpq_version.o

$(outtmp)/libpq_util.o :$(libpq)/src/util.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/util.cxx -o $(outtmp)/libpq_util.o

$(outtmp)/libpq_transaction_base.o :$(libpq)/src/transaction_base.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/transaction_base.cxx -o $(outtmp)/libpq_transaction_base.o

$(outtmp)/libpq_transaction.o :$(libpq)/src/transaction.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/transaction.cxx -o $(outtmp)/libpq_transaction.o

$(outtmp)/libpq_tablewriter.o :$(libpq)/src/tablewriter.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/tablewriter.cxx -o $(outtmp)/libpq_tablewriter.o

$(outtmp)/libpq_tablestream.o :$(libpq)/src/tablestream.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/tablestream.cxx -o $(outtmp)/libpq_tablestream.o

$(outtmp)/libpq_tablereader.o :$(libpq)/src/tablereader.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/tablereader.cxx -o $(outtmp)/libpq_tablereader.o

$(outtmp)/libpq_substransaction.o :$(libpq)/src/subtransaction.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/subtransaction.cxx -o $(outtmp)/libpq_substransaction.o

$(outtmp)/libpq_stream_to.o :$(libpq)/src/stream_to.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/stream_to.cxx -o $(outtmp)/libpq_stream_to.o

$(outtmp)/libpq_stream_from.o :$(libpq)/src/stream_from.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/stream_from.cxx -o $(outtmp)/libpq_stream_from.o

$(outtmp)/libpq_stream_base.o :$(libpq)/src/stream_base.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/stream_base.cxx -o $(outtmp)/libpq_stream_base.o

$(outtmp)/libpq_strconv.o :$(libpq)/src/strconv.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/strconv.cxx -o $(outtmp)/libpq_strconv.o

$(outtmp)/libpq_statement_parameters.o :$(libpq)/src/statement_parameters.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/statement_parameters.cxx -o $(outtmp)/libpq_statement_parameters.o

$(outtmp)/libpq_sql_cursor.o :$(libpq)/src/sql_cursor.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/sql_cursor.cxx -o $(outtmp)/libpq_sql_cursor.o

$(outtmp)/libpq_row.o :$(libpq)/src/row.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/row.cxx -o $(outtmp)/libpq_row.o

$(outtmp)/libpq_robusttransaction.o :$(libpq)/src/robusttransaction.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/robusttransaction.cxx -o $(outtmp)/libpq_robusttransaction.o

$(outtmp)/libpq_result.o :$(libpq)/src/result.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/result.cxx -o $(outtmp)/libpq_result.o

$(outtmp)/libpq_prepared_statement.o :$(libpq)/src/prepared_statement.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/prepared_statement.cxx -o $(outtmp)/libpq_prepared_statement.o

$(outtmp)/libpq_pipeline.o :$(libpq)/src/pipeline.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/pipeline.cxx -o $(outtmp)/libpq_pipeline.o

$(outtmp)/libpq_notification.o :$(libpq)/src/notification.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/notification.cxx -o $(outtmp)/libpq_notification.o

$(outtmp)/libpq_nontransaction.o :$(libpq)/src/nontransaction.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/nontransaction.cxx -o $(outtmp)/libpq_nontransaction.o

$(outtmp)/libpq_largeobject.o :$(libpq)/src/largeobject.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/largeobject.cxx -o $(outtmp)/libpq_largeobject.o

$(outtmp)/libpq_field.o :$(libpq)/src/field.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/field.cxx -o $(outtmp)/libpq_field.o

$(outtmp)/libpq_except.o :$(libpq)/src/except.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/except.cxx -o $(outtmp)/libpq_except.o

$(outtmp)/libpq_errorhandler.o :$(libpq)/src/errorhandler.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/errorhandler.cxx -o $(outtmp)/libpq_errorhandler.o

$(outtmp)/libpq_encodings.o :$(libpq)/src/encodings.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/encodings.cxx -o $(outtmp)/libpq_encodings.o

$(outtmp)/libpq_dbtransaction.o :$(libpq)/src/dbtransaction.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/dbtransaction.cxx -o $(outtmp)/libpq_dbtransaction.o

$(outtmp)/libpq_cursor.o :$(libpq)/src/cursor.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/cursor.cxx -o $(outtmp)/libpq_cursor.o

$(outtmp)/libpq_connection_base.o :$(libpq)/src/connection_base.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/connection_base.cxx -o $(outtmp)/libpq_connection_base.o

$(outtmp)/libpq_connection.o :$(libpq)/src/connection.cxx
	$(cppcompiler) $(cppflags)  $(libpq_include) -c $(libpq)/src/connection.cxx -o $(outtmp)/libpq_connection.o

$(outtmp)/libpq_array.o :$(libpq)/src/array.cxx
	$(cppcompiler) $(cppflags) $(libpq_include) -c $(libpq)/src/array.cxx -o $(outtmp)/libpq_array.o

$(outtmp)/libpq_binarystring.o :$(libpq)/src/binarystring.cxx
	$(cppcompiler) $(cppflags) $(libpq_include) -c $(libpq)/src/binarystring.cxx -o $(outtmp)/libpq_binarystring.o

