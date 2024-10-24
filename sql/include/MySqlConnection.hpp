#ifndef __OBOTCHA_MY_SQL_CONNECTION_H__
#define __OBOTCHA_MY_SQL_CONNECTION_H__

#include "mysql.h"

#include "Object.hpp"
#include "ArrayList.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"
#include "Mutex.hpp"
#include "SqlConnection.hpp"

namespace obotcha {

DECLARE_CLASS(MySqlConnection) IMPLEMENTS(SqlConnection) {
public:
    _MySqlConnection();

    int connect(SqlConnectParam args);

    int count(SqlQuery query);
    
    SqlRecords query(SqlQuery query);

    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        return st(SqlConnection)::query<T>(query);
    }

    int exec(SqlQuery);

    int close() final;

    int startTransaction();

    int commitTransaction();

    int rollabckTransaction();

    ~_MySqlConnection();

    void queryWithEachRow(SqlQuery query,onRowStartCallback,onRowNewDataCallback,onRowEndCallback);

private:
    MYSQL mysql;
    Mutex mMutex;
};

} // namespace obotcha
#endif