#include "Sqlite3Connection.hpp"
#include "sqlite3.h"

namespace obotcha {

String _Sqlite3Connection::SQLITE3_CONNECT_TAG_PATH = "path";

int _Sqlite3Connection::connect(HashMap<String,String>args) {
    mPath = args->get(SQLITE3_CONNECT_TAG_PATH);
    if(mPath == nullptr) {
        return -Sqlite3FailWrongParam;
    }

    int result = sqlite3_open(mPath->toChars(), &mSqlDb);
    if(result < 0) {
        return -Sqlite3FailOpen;
    }

    return 0;
}

ArrayList<SqlRecord> _Sqlite3Connection::query(String sqlString,SqlRecordBuilder rec) {
    ArrayList<SqlRecord> records = createArrayList<SqlRecord>();
    SqliteQueryParam param;
    param.l = records;
    param.r = rec;

    if (sqlite3_exec(mSqlDb, sqlString->toChars(), sqlQueryCallback, &param,NULL) != SQLITE_OK) {
        return nullptr;
    }
    return records;
}


int _Sqlite3Connection::exec(String sqlstring) {
    if(mPath == nullptr) {
        return -Sqlite3FailNoDb;
    }

    if(SQLITE_OK != sqlite3_exec(mSqlDb, sqlstring->toChars(), NULL,NULL,NULL)) {
        return -Sqlite3FailExecErr;
    }

    return 0;
}

int _Sqlite3Connection::sqlQueryCallback(void *ctx, int argc, char *argv[], char *col[]) {
    SqliteQueryParam *param = (SqliteQueryParam *)ctx;
    SqlRecord r = param->r->create();
    for (int i = 0; i < argc; i++) {
        sql_data_set m = r->getSqlAssignment(i,col[i]);
        if(m == nullptr) {
            continue;
        }
        m(r.get_pointer(),argv[i]);
    }

    param->l->add(r);

    return 0;
}

int _Sqlite3Connection::startTransaction() {
    int ret = sqlite3_exec(mSqlDb,"begin transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -Sqlite3FailTransactionErr;
    }

    return 0;
}

int _Sqlite3Connection::commitTransaction() {
    int ret = sqlite3_exec(mSqlDb,"commit transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -Sqlite3FailTransactionErr;
    }

    return 0;
}

int _Sqlite3Connection::rollabckTransaction() {
    int ret = sqlite3_exec(mSqlDb,"rollback transaction",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -Sqlite3FailTransactionErr;
    }

    return 0;
}

int _Sqlite3Connection::close() {
    //TODO
}

};
