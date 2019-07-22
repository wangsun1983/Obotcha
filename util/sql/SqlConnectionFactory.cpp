#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlRecord.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "SqlConnectionFactory.hpp"
#include "Sqlite3Connection.hpp"
#include "MySqlConnection.hpp"

namespace obotcha {

SqlConnection _SqlConnectionFactory::generateConn(int type) {
    switch(type) {
        case SqlConnection_Sqlite3:
        return createSqlite3Connection();

        case SqlConnection_MySql:
        return createMySqlConnection();
    }

    return nullptr;
}











}