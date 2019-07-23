#ifndef __SQL_CONNECTION_H__
#define __SQL_CONNECTION_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "SqlRecord.hpp"
#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SqlConnection) {
public:
    virtual int connect(HashMap<String,String>args) = 0;

    virtual ArrayList<SqlRecord> query(String,SqlRecordBuilder) = 0;

    virtual int exec(String) = 0;

    virtual int close() = 0;

    virtual int startTransaction(){};

    virtual int commitTransaction(){};

    virtual int rollabckTransaction(){};
};

}


#endif