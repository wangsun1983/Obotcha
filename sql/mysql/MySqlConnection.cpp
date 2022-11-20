#include "MySqlConnection.hpp"
#include "SqlConnection.hpp"
#include "Error.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"
#include "MySqlConnectParam.hpp"

namespace obotcha {


_MySqlConnection::_MySqlConnection() {
    mType = MySqlConnection;
}

int _MySqlConnection::connect(SqlConnectParam param) {
    mMutex = createMutex();
    auto arg = Cast<MySqlConnectParam>(param);

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
    String password = arg->getPassword();
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
        LOG(ERROR)<<"mysql connect failed,reason is "<<mysql_error(&mysql);
        return -1;
    }
    return 0;
}

SqlRecords _MySqlConnection::query(SqlQuery query) {
    String sql = query->toString();
    mMutex->lock();
    int ret = mysql_real_query(&mysql, sql->toChars(),sql->size());
    if(ret == 0) {
        MYSQL_RES *res = mysql_store_result(&mysql);
        mMutex->unlock();
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

    mMutex->unlock();
    return nullptr;
}

int _MySqlConnection::exec(SqlQuery query) {
    String sql = query->toString();
    AutoLock l(mMutex);
    return mysql_real_query(&mysql, sql->toChars(),sql->size());
}

int _MySqlConnection::count(SqlQuery query) {
    String sql = query->toString();
    mMutex->lock();
    mysql_real_query(&mysql, sql->toChars(),sql->size());
    MYSQL_RES *res = mysql_store_result(&mysql);
    mMutex->unlock();
    
    MYSQL_ROW row = mysql_fetch_row(res);
    int resut = createString(row[0])->toBasicInt();
    mysql_free_result(res);
    return resut;
}

int _MySqlConnection::startTransaction() {
    return mysql_query(&mysql,"BEGIN");
}

int _MySqlConnection::commitTransaction() {
    return mysql_query(&mysql,"COMMIT");
}

int _MySqlConnection::rollabckTransaction() {
    return mysql_query(&mysql,"ROLLBACK");
}

int _MySqlConnection::close() {
    mysql_close(&mysql);
    return 0;
}

_MySqlConnection::~_MySqlConnection() {
    this->close();
}

void _MySqlConnection::queryWithEachRow(SqlQuery query,onRowStartCallback onStart,onRowNewDataCallback onData,onRowEndCallback onEnd) {
    String sql = query->toString();
    int ret = mysql_real_query(&mysql, sql->toChars(),sql->size());
    
    if(ret == 0) {
        MYSQL_RES *res = mysql_store_result(&mysql);
        int columnNum = mysql_num_fields(res);
        List<String> columns = createList<String>(columnNum);
        if (res != nullptr) {
            for(int i=0; i < columnNum; i++) {
                MYSQL_FIELD *field = mysql_fetch_field_direct(res,i);
                columns[i] = createString(field->name);
            }
            
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                onStart();
                for (int i = 0; i < columnNum; i++) {
                    if(row[i] != nullptr) {
                        onData(createString(columns[i]),createString(row[i]));
                    }
                }
                onEnd();
            }
        }
        mysql_free_result(res);
    }
}

}
