#ifndef __OBOTCHA_MY_SQL_CONNECTION_H__
#define __OBOTCHA_MY_SQL_CONNECTION_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlRecord.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "SqlConnection.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(MySqlConnection) IMPLEMENTS(SqlConnection){
public:
    int connect(HashMap<String,String>args);

    ArrayList<SqlRecord> query(String,SqlRecordBuilder);

    int exec(String);

    int close();
};
}

#endif