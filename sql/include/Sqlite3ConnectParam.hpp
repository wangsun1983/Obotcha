#ifndef __OBOTCHA_MY_SQLITE3_CONNECT_PARAM_H__
#define __OBOTCHA_MY_SQLITE3_CONNECT_PARAM_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "SqlConnectParam.hpp"

namespace obotcha {

DECLARE_CLASS(Sqlite3ConnectParam) IMPLEMENTS(SqlConnectParam){
public:
    static const String Path;
    
    void setPath(String);

    String getPath();
};

} // namespace obotcha
#endif