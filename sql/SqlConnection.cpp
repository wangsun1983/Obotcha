#include "SqlConnection.hpp"

namespace obotcha {

const String _SqlConnection::MySqlParamHost = createString("host");
const String _SqlConnection::MySqlParamUser = createString("user");
const String _SqlConnection::MySqlParamPassword = createString("password");;
const String _SqlConnection::MySqlParamDbName = createString("dbname");;
const String _SqlConnection::MySqlParamPort = createString("port");;
const String _SqlConnection::MySqlParamUnixSocketName = createString("unixsock");
const String _SqlConnection::MySqlParamClientFlg = createString("flag");

const String _SqlConnection::Sqlite3ParamPath = createString("path");

const String _SqlConnection::MySqlLocalHost = createString("host");

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
