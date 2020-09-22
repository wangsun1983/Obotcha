#include "sqlite3.h"

#include "MySqlClient.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

/*
(MYSQL *mysql,const char *host, const char *user,
		       const char *passwd, const char *db,
		       uint port, const char *unix_socket,ulong client_flag)
*/

const String _MySqlClient::ParamHost = createString("host");
const String _MySqlClient::ParamUser = createString("user");
const String _MySqlClient::ParamPassword = createString("password");;
const String _MySqlClient::ParamDbName = createString("dbname");;
const String _MySqlClient::ParamPort = createString("port");;
const String _MySqlClient::ParamUnixSocketName = createString("unixsock");
const String _MySqlClient::ParamClientFlg = createString("flag");

const String _MySqlClient::LocalHost = createString("host");

int _MySqlClient::connect(HashMap<String,String>args) {
    if (mysql_init(&mysql) == nullptr) {
        LOG(ERROR)<<"mysql init fail";
        return -1;  
    }  

    String host = args->get(ParamHost);
    if(host == nullptr) {
        host = LocalHost;
    }
    const char *param_host = host->toChars();

    String user = args->get(ParamUser);
    const char *param_user = nullptr;
    if(user != nullptr) {
        param_user = user->toChars();
    }

    String password = args->get(ParamPassword);
    const char *param_password = nullptr;
    if(password != nullptr) {
        param_password = password->toChars();
    }

    String db = args->get(ParamDbName);
    const char *param_db = nullptr;
    if(db != nullptr) {
        param_db = db->toChars();
    }
    
    int param_port = 0;
    String portStr = args->get(ParamPort);
    if(portStr != nullptr) {
        param_port = portStr->toBasicInt();
    }

    String unixsock = args->get(ParamUnixSocketName);
    const char *param_unixsock = nullptr;
    if(unixsock != nullptr) {
        param_unixsock = unixsock->toChars();
    }

    uint64_t param_flag = 0;
    String clientflag = args->get(ParamClientFlg);
    if(clientflag != nullptr) {
        param_flag = clientflag->toBasicUint64();
    }
    
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

int _MySqlClient::exec(SqlQuery) {
    
    return 0;
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
    //TODO
    return 0;
}

};
