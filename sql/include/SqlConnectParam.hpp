#ifndef __OBOTCHA_SQL_CONNECT_PARAM_H__
#define __OBOTCHA_SQL_CONNECT_PARAM_H__

#include "sqlite3.h"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "ReflectUtil.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"

namespace obotcha {

DECLARE_CLASS(SqlConnectParam) {

public:
    _SqlConnectParam();

    void set(String,String);

    template <typename T>
    void set(String key ,T value) {
        mParams->put(key,st(String)::valueOf(value));
    }

    String get(String);

protected:
    HashMap<String,String> mParams;
};

} // namespace obotcha
#endif