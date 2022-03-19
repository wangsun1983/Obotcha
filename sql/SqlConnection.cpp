#include "SqlConnection.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

int _SqlConnection::connect(SqlConnectParam args) {
    if(IsInstance(MySqlConnectParam,args)) {
        mType = MySqlConnection;
        return mMySqlClient->connect(Cast<MySqlConnectParam>(args));
    } else if(IsInstance(Sqlite3ConnectParam,args)) {
        mType = Sqlite3Connection;
        return mSqlite3Client->connect(Cast<Sqlite3ConnectParam>(args));
    }
    return -1;
}

_SqlConnection::_SqlConnection() {
    mType = -1;
}

int _SqlConnection::exec(SqlQuery query) {
    switch(mType) {
        case MySqlConnection:
            return mMySqlClient->exec(query);
        break;

        case Sqlite3Connection:
            return mSqlite3Client->exec(query);
        break;
    }

    return -1;
}
    
SqlRecords _SqlConnection::query(SqlQuery query) {
    switch(mType) {
        case MySqlConnection:
            return mMySqlClient->query(query);
        break;

        case Sqlite3Connection:
            return mSqlite3Client->query(query);
        break;
    }

    return nullptr;
}

}
