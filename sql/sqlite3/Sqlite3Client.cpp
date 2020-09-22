#include "sqlite3.h"

#include "Sqlite3Client.hpp"
#include "Error.hpp"
#include "SqlRecords.hpp"

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

SqlRecords _Sqlite3Client::query(SqlQuery query) {
    String sql = query->toString();
    char **dbResult;
    int nRow, nColumn;
    char *errmsg = NULL;
    printf("wangsl,Sqlite3Client trace1\n");
    if(sqlite3_get_table(mSqlDb, sql->toChars(), &dbResult, &nRow, &nColumn, &errmsg) == SQLITE_OK) {
        printf("wangsl,Sqlite3Client trace2,nRow is %d,nColumn is %d\n",nRow,nColumn);
        SqlRecords records = createSqlRecords(nRow,nColumn);
        int index = nColumn;
        for (int i = 0; i < nRow; i++) {
            List<String> row = createList<String>(nColumn);
            for (int j = 0; j < nColumn; j++) {
                printf("wangsl,Sqlite3Client trace3,dbResult is %s\n",dbResult[index]);
                row[j] = createString(dbResult[index]);
                index++;
            }
            records->setOneRow(i,row);
        }
        printf("wangsl,Sqlite3Client trace4\n");
        return records;
    }

    return nullptr;
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
