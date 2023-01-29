#include "sqlite3.h"

#include "Sqlite3Connection.hpp"
#include "SqlRecords.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

namespace obotcha {

int _Sqlite3Connection::connect(SqlConnectParam param) {
    mMutex = createMutex();

    auto arg = Cast<Sqlite3ConnectParam>(param);
    mPath = arg->getPath();
    if(mPath == nullptr) {
        return -EINVAL;
    }

    int result = sqlite3_open(mPath->toChars(), &mSqlDb);
    isClosed = false;

    return result;
}

SqlRecords _Sqlite3Connection::query(SqlQuery query) {
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

int _Sqlite3Connection::count(SqlQuery query) {
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

int _Sqlite3Connection::exec(SqlQuery query) {
    if(mPath == nullptr) {
        return -1;
    }

    String sqlstring = query->toString();
    char *errmsg = NULL;
    mMutex->lock();
    if(SQLITE_OK != sqlite3_exec(mSqlDb, sqlstring->toChars(), nullptr,nullptr,&errmsg)) {
        LOG(ERROR)<<"Sqlite3 exec error,reason is "<<errmsg<<",sql is "<<sqlstring->toChars();
        mMutex->unlock();
        sqlite3_free(errmsg);
        return -1;
    }
    mMutex->unlock();
    return 0;
}

int _Sqlite3Connection::startTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"BEGIN",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -1;
    }

    return 0;
}

int _Sqlite3Connection::commitTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"COMMIT",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -1;
    }

    return 0;
}

int _Sqlite3Connection::rollabckTransaction() {
    AutoLock l(mMutex);
    int ret = sqlite3_exec(mSqlDb,"ROLLBACK",0,0,nullptr);
    if(ret != SQLITE_OK) {
        return -1;
    }

    return 0;
}

void _Sqlite3Connection::queryWithEachRow(SqlQuery query,
                                          onRowStartCallback onStart,
                                          onRowNewDataCallback onData,
                                          onRowEndCallback onEnd) {
    String sql = query->toString();
        char **dbResult;
        int nRow, nColumn;
        char *errmsg = NULL;
        
        mMutex->lock();
        int result = sqlite3_get_table(mSqlDb, sql->toChars(), &dbResult, &nRow, &nColumn, &errmsg);
        mMutex->unlock();
        if (SQLITE_OK == result) {
            int index = nColumn;
            for (int i = 0; i < nRow; i++) {
                onStart();
                for (int j = 0; j < nColumn; j++) {
                    //printf( “字段名:%s ?> 字段值:%s\n”, dbResult[j], dbResult [index] );
                    // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，
                    //从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
                    //Field field = data->getField(createString(dbResult[j]));
                    String name = createString(dbResult[j]);
                    auto value_ptr = dbResult[index];
                    String value = (value_ptr!=nullptr)?createString(value_ptr):nullptr;
                    onData(name,value);
                    index++;
                }
                onEnd();
            }
            sqlite3_free_table(dbResult);
        } else {
            LOG(ERROR)<<"Sqlite3 query error,reason is "<<errmsg;
            sqlite3_free(errmsg);
        }
}


int _Sqlite3Connection::close() {
    AutoLock l(mMutex);
    isClosed = true;
    return sqlite3_close(mSqlDb);
}

_Sqlite3Connection::~_Sqlite3Connection() {
    close();
}

};
