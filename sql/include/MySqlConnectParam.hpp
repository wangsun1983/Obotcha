#ifndef __OBOTCHA_MY_SQL_CONNECT_PARAM_H__
#define __OBOTCHA_MY_SQL_CONNECT_PARAM_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "SqlConnectParam.hpp"

namespace obotcha {

DECLARE_CLASS(MySqlConnectParam) IMPLEMENTS(SqlConnectParam){
public:
    static const String Host;
    static const String User;
    static const String Password;
    static const String DbName;
    static const String Port;
    static const String UnixSocketName;
    static const String ClientFlg;

    void setHost(String);
    void setUser(String);
    void setPassword(String);
    void setDbName(String);
    void setPort(int port);
    void setSocketName(String);
    void setClientFlag(uint64_t);

    String getHost();
    String getUser();
    String getPassword();
    String getDbName();
    int getPort();
    String getSocketName();
    uint64_t getClientFlag();
};

} // namespace obotcha
#endif