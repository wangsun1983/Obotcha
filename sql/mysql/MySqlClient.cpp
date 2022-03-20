#include "sqlite3.h"

#include "MySqlClient.hpp"
#include "SqlConnection.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

int _MySqlClient::connect(MySqlConnectParam arg) {
    if (mysql_init(&mysql) == nullptr) {
        LOG(ERROR)<<"mysql init fail";
        return -1;  
    }  

    String host = arg->getHost();
    if(host == nullptr) {
        host = "host";
    }
    const char *param_host = host->toChars();

    String user = arg->getUser();
    const char *param_user = nullptr;
    if(user != nullptr) {
        param_user = user->toChars();
    }

    String password = arg->getUser();
    const char *param_password = nullptr;
    if(password != nullptr) {
        param_password = password->toChars();
    }

    String db = arg->getDbName();
    const char *param_db = nullptr;
    if(db != nullptr) {
        param_db = db->toChars();
    }
    
    int param_port = arg->getPort();
    
    String unixsock = arg->getSocketName();
    const char *param_unixsock = nullptr;
    if(unixsock != nullptr) {
        param_unixsock = unixsock->toChars();
    }

    uint64_t param_flag = arg->getClientFlag();
    
    if(nullptr ==  mysql_real_connect(&mysql,
                                    param_host,
                                    param_user,
                                    param_password,
                                    param_db,
                                    param_port,
                                    param_unixsock,
                                    param_flag)) {
        LOG(ERROR)<<"mysql connect failed";
        return -1;
    }

    return 0;
}

SqlRecords _MySqlClient::query(SqlQuery query) {
    String sql = query->toString();
    int ret = mysql_real_query(&mysql, sql->toChars(),sql->size());
    if(ret == 0) {
        MYSQL_RES *res = nullptr;
        res = mysql_store_result(&mysql);
        int columnNum = mysql_num_fields(res);
        int rowNum = mysql_num_rows(res);
        SqlRecords records = createSqlRecords(rowNum,columnNum);

        MYSQL_ROW row;
        int count = 0;
        while ((row = mysql_fetch_row(res))) {
            List<String> rowData = createList<String>(columnNum);
            for (int i = 0; i < columnNum; i++) {
                rowData[i] = createString(row[i]);
            }
            records->setOneRow(count,rowData);
            count++;
        }

        mysql_free_result(res);
        return records;
    }

    return nullptr;
}

int _MySqlClient::exec(SqlQuery query) {
    String sql = query->toString();
    return mysql_real_query(&mysql, sql->toChars(),sql->size());
}

int _MySqlClient::startTransaction() {
    
    return 0;
}

int _MySqlClient::commitTransaction() {
    
    return 0;
}

int _MySqlClient::rollabckTransaction() {
    
    return 0;
}

int _MySqlClient::close() {
    mysql_close(&mysql);
    return 0;
}

};
