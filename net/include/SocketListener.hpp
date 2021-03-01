#ifndef __OBOTCHA_SOCKET_LISTENER_HPP__
#define __OBOTCHA_SOCKET_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "SocketResponser.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketListener) {
public:
    //virtual void onAcceptTcp(int fd,ByteArray pack) {};
    virtual void onDataReceived(SocketResponser r,ByteArray pack) = 0;

    virtual void onDisconnect(SocketResponser r) = 0;

    virtual void onConnect(SocketResponser r) = 0;
    
    //virtual void onAcceptTcp(int fd,ByteArray pack) {};
    //virtual void onTimeout() = 0;
};

/*
template<class ConnectFunction,class... ConnectArgs,class DisconnectFunction,class... DisconnectArgs,class DataFunction,class... DataArgs> 
class(_LambdaScoektListener) {
public:
    _LambdaScoektListener(ConnectFunction &&f1,ConnectArgs&&... args1,
                          DisconnectFunction &&f2,DisconnectArgs&&... args2,
                          DataFunction &&f3,DataArgs ...arg3):_connectFunc(f1),_connectArgs(std::make_tuple(arg1...)),
                                                              _disconnectFunc(f2),_disconnectArgs(std::make_tuple(arg2...)),
                                                              _dataFunc(f3),_dataArgs(std::make_tuple(arg3...)) {
        //TODO
    }

    void onDataReceived(SocketResponser r,ByteArray pack) {
        //TODO
    }

    void onDisconnect(SocketResponser r) {
        //TODO
    }

    void onConnect(SocketResponser r) {
        //TODO
    }

private:
    ConnectFunction _connectFunc;
    DisconnectFunction _disconnectFunc;
    DataFunction _dataFunc;

    std::tuple<ConnectArgs...> _connectArgs; 
    std::tuple<DisconnectArgs...> _disconnectArgs;
    std::tuple<DataArgs...> _dataArgs;
};
*/
}
#endif
