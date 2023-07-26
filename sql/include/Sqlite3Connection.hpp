#ifndef __OBOTCHA_SQLITE3_CONNECTION_H__
#define __OBOTCHA_SQLITE3_CONNECTION_H__

#include "sqlite3.h"

#include "Object.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "ReflectUtil.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"
#include "Sqlite3ConnectParam.hpp"
#include "AtomicBoolean.hpp"
#include "Log.hpp"
#include "SqlConnection.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(Sqlite3Connection) IMPLEMENTS(SqlConnection) {

public:
    int connect(SqlConnectParam args) override;
    
    SqlRecords query(SqlQuery query) override;

    int count(SqlQuery) override;

    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        return st(SqlConnection)::query<T>(query);
    }

    int exec(SqlQuery) override;

    int close() override final;

    int startTransaction() override;

    int commitTransaction() override;

    int rollabckTransaction() override;

    ~_Sqlite3Connection();

    void queryWithEachRow(SqlQuery query,
                          onRowStartCallback,
                          onRowNewDataCallback,
                          onRowEndCallback) override;

private:
    sqlite3 *mSqlDb;

    String mPath;

    bool isClosed;

    //maybe we should use this mutex to make one client one operation.
    Mutex mMutex;
};

} // namespace obotcha
#endif