#include "sqlite3.h"

#include "Sqlite3Client.hpp"
#include "Error.hpp"

namespace obotcha {

String _Sqlite3Client::SQLITE3_CONNECT_TAG_PATH = "path";

int _Sqlite3Client::connect(HashMap<String,String>args) {
    mPath = args->get(SQLITE3_CONNECT_TAG_PATH);
    if(mPath == nullptr) {
        return -SqlFailWrongParam;
    }

    int result = sqlite3_open(mPath->toChars(), &mSqlDb);
    if(result < 0) {
        return -SqlFailOpen;
    }

    return 0;
}

int _Sqlite3Client::count(String) {
    //int result = sqlite3_data_count()
    //TODO
    return -1;
}

int _Sqlite3Client::exec(SqlQuery query) {
    if(mPath == nullptr) {
        return -SqlFailNoDb;
    }

    String sqlstring = query->toString();
    if(SQLITE_OK != sqlite3_exec(mSqlDb, sqlstring->toChars(), NULL,NULL,NULL)) {
        return -SqlExecFail;
    }

    return 0;
}

int _Sqlite3Client::startTransaction() {
    int ret = sqlite3_exec(mSqlDb,"begin transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::commitTransaction() {
    int ret = sqlite3_exec(mSqlDb,"commit transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::rollabckTransaction() {
    int ret = sqlite3_exec(mSqlDb,"rollback transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::close() {
    //TODO
    return 0;
}

};