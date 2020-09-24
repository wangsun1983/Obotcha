#ifndef __OBOTCHA_SQL_CONNECTION_HPP__
#define __OBOTCHA_SQL_CONNECTION_HPP__

#include <map>
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ArrayList.hpp"
#include "MySqlClient.hpp"
#include "Sqlite3Client.hpp"

namespace obotcha {

enum {
    MySqlConnection = 0,
    Sqlite3Connection
};

DECLARE_SIMPLE_CLASS(SqlConnection) {

public:
    static const String MySqlParamHost;
    static const String MySqlParamUser;
    static const String MySqlParamPassword;
    static const String MySqlParamDbName;
    static const String MySqlParamPort;
    static const String MySqlParamUnixSocketName;
    static const String MySqlParamClientFlg;

    static const String Sqlite3ParamPath;

    static const String MySqlLocalHost;

    _SqlConnection(int);

    int exec(SqlQuery query);
    
    SqlRecords query(SqlQuery query);

    int connect(HashMap<String,String>args);

    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        switch(mType) {
        case MySqlConnection:
            return mMySqlClient->query<T>(query);
        break;

        case Sqlite3Connection:
            return mSqlite3Client->query<T>(query);
        break;
        }
    }

private:
    int mType;

    MySqlClient mMySqlClient;
    
    Sqlite3Client mSqlite3Client;
};

}

#endif