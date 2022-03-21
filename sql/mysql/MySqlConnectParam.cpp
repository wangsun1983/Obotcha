#include "MySqlConnectParam.hpp"
#include "Uint64.hpp"

namespace obotcha {

const String _MySqlConnectParam::Host = createString("host");
const String _MySqlConnectParam::User = createString("user");
const String _MySqlConnectParam::Password = createString("password");
const String _MySqlConnectParam::DbName = createString("dbname");
const String _MySqlConnectParam::Port = createString("port");
const String _MySqlConnectParam::UnixSocketName = createString("unixsock");
const String _MySqlConnectParam::ClientFlg = createString("flag");

void _MySqlConnectParam::setHost(String host) {
    mParams->put(Host,host);
}

void _MySqlConnectParam::setUser(String user) {
    mParams->put(User,user);
}

void _MySqlConnectParam::setPassword(String password) {
    mParams->put(Password,password);
}

void _MySqlConnectParam::setDbName(String dbname) {
    mParams->put(DbName,dbname);
}

void _MySqlConnectParam::setPort(int port) {
    mParams->put(Port,st(String)::valueOf(port));
}

void _MySqlConnectParam::setSocketName(String socketname) {
    mParams->put(UnixSocketName,socketname);
}

void _MySqlConnectParam::setClientFlag(uint64_t flag) {
    mParams->put(ClientFlg,st(String)::valueOf(flag));
}

String _MySqlConnectParam::getHost() {
    return mParams->get(Host);
}

String _MySqlConnectParam::getUser() {
    return mParams->get(User);
}

String _MySqlConnectParam::getPassword() {
    return mParams->get(Password);
}

String _MySqlConnectParam::getDbName() {
    return mParams->get(DbName);
}

int _MySqlConnectParam::getPort() {
    String value = mParams->get(Port);
    if(value != nullptr) {
        return value->toBasicInt();
    }

    return -1;
}

String _MySqlConnectParam::getSocketName() {
    return mParams->get(UnixSocketName);
}

uint64_t _MySqlConnectParam::getClientFlag() {
    String value = mParams->get(ClientFlg);
    if(value != nullptr) {
        return value->toBasicUint64();
    }

    return 0;
}

} // namespace obotcha
