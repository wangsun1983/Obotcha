#include "SqlConnection.hpp"

namespace obotcha {

int _SqlConnection::connect(HashMap<String,String>args) {
    switch(mType) {
        case MySqlConnection:
            return mMySqlClient->connect(args);
        break;

        case Sqlite3Connection:
            return mSqlite3Client->connect(args);
        break;
    }

    return -1;
}

_SqlConnection::_SqlConnection(int type) {
    mType = type;
    switch(type) {
        case MySqlConnection:
            mMySqlClient = createMySqlClient();
        break;

        case Sqlite3Connection:
            mSqlite3Client = createSqlite3Client();
        break;

    }
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
