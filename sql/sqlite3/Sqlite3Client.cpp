#include "sqlite3.h"

#include "Sqlite3Client.hpp"
#include "Error.hpp"
#include "SqlRecords.hpp"
#include "SqlConnection.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

namespace obotcha {

int _Sqlite3Client::connect(Sqlite3ConnectParam arg) {
    mMutex = createMutex();
    mPath = arg->getPath();
    if(mPath == nullptr) {
        return -SqlFailWrongParam;
    }

    int result = sqlite3_open(mPath->toChars(), &mSqlDb);
    if(result < 0) {
        return -SqlFailOpen;
    }

    isClosed = false;

    return 0;
}

SqlRecords _Sqlite3Client::query(SqlQuery query) {
    String sql = query->toString();
    char **dbResult;
    int nRow, nColumn;
    char *errmsg = NULL;
    mMutex->lock();
    if(sqlite3_get_table(mSqlDb, sql->toChars(), &dbResult, &nRow, &nColumn, &errmsg) == SQLITE_OK) {
        mMutex->unlock();
        SqlRecords records = createSqlRecords(nRow,nColumn);
        int index = nColumn;
        for (int i = 0; i < nRow; i++) {
            List<String> row = createList<String>(nColumn);
            for (int j = 0; j < nColumn; j++) {
                row[j] = createString(dbResult[index]);
                index++;
            }
            records->setOneRow(i,row);
        }
        sqlite3_free_table(dbResult);
        return records;
    }
    mMutex->unlock();
    return nullptr;
}

int _Sqlite3Client::count(SqlQuery query) {
    const char *sql = query->toString()->toChars();
    char **dbResult;
    int nRow = 0;
    int nColumn = 0;
    char *errmsg = NULL;
    mMutex->lock();
    if(sqlite3_get_table(mSqlDb, sql, &dbResult, &nRow, &nColumn, &errmsg) == SQLITE_OK) {
        mMutex->unlock();
        char *data = dbResult[1];
        if(data != nullptr) {
            int rs = createString(data)->toBasicInt();
            sqlite3_free_table(dbResult);
            return rs;
        }
        sqlite3_free_table(dbResult);
    } else {
        LOG(ERROR)<<"Sqlite3 Count error,reason is "<<errmsg;
        sqlite3_free(errmsg);
    }
    mMutex->unlock();
    return 0;
}

int _Sqlite3Client::exec(SqlQuery query) {
    if(mPath == nullptr) {
        return -SqlFailNoDb;
    }

    String sqlstring = query->toString();
    char *errmsg = NULL;
    mMutex->lock();
    if(SQLITE_OK != sqlite3_exec(mSqlDb, sqlstring->toChars(), nullptr,nullptr,&errmsg)) {
        LOG(ERROR)<<"Sqlite3 exec error,reason is "<<errmsg;
        mMutex->unlock();
        sqlite3_free(errmsg);
        return -SqlExecFail;
    }
    mMutex->unlock();
    return 0;
}

int _Sqlite3Client::startTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"BEGIN",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::commitTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"COMMIT",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::rollabckTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"ROLLBACK",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -SqlTransactionFail;
    }

    return 0;
}

int _Sqlite3Client::close() {
    AutoLock l(mMutex);
    isClosed = true;
    return sqlite3_close(mSqlDb);
}

_Sqlite3Client::~_Sqlite3Client() {
    close();
}

};
