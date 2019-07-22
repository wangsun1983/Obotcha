#ifndef __SQL_CONNECTION_FACTORY_H__
#define __SQL_CONNECTION_FACTORY_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlRecord.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "SqlConnection.hpp"

namespace obotcha {

enum SqlConnectionEnum {
    SqlConnection_Sqlite3 = 0,
    SqlConnection_MySql,
};

DECLARE_SIMPLE_CLASS(SqlConnectionFactory) {
public:
    static SqlConnection generateConn(int type);
};

}


#endif