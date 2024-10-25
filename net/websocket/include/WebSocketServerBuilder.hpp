#ifndef __OBOTCHA_WEBSOCKET_SERVER_BUILDER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_BUILDER_HPP__

#include "Object.hpp"
#include "InetAddress.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketServer.hpp"

namespace obotcha {

//------------------------WebSocketServer-------------------------
DECLARE_CLASS(WebSocketServerBuilder) {
public:
    _WebSocketServerBuilder() = default;
    _WebSocketServerBuilder* setInetAddr(InetAddress addr);
    _WebSocketServerBuilder* setOption(HttpOption option);
    _WebSocketServerBuilder* addListener(String path,WebSocketListener l);
    _WebSocketServerBuilder* setThreadNum(int);

    WebSocketServer build();
private:
    InetAddress mAddr;
    int threadNum = kDefaultThreadNum;
    HttpOption httpoption = nullptr;
    ArrayList<Pair<String,WebSocketListener>> pairs = ArrayList<Pair<String,WebSocketListener>>::New();
    static const int kDefaultThreadNum;
};

} // namespace obotcha
#endif
