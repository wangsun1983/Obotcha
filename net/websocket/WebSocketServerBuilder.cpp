#include "WebSocketServerBuilder.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

const int _WebSocketServerBuilder::kDefaultThreadNum = 4;

_WebSocketServerBuilder::_WebSocketServerBuilder(){
    pairs = createArrayList<Pair<String,WebSocketListener>>();
    threadNum = kDefaultThreadNum;
    httpoption = nullptr;
}

_WebSocketServerBuilder* _WebSocketServerBuilder::setInetAddr(InetAddress addr) {
    this->addr = addr;
    return this;
}

_WebSocketServerBuilder* _WebSocketServerBuilder::setOption(HttpOption option) {
    this->httpoption = option;
    return this;
}

_WebSocketServerBuilder* _WebSocketServerBuilder::addListener(String path,WebSocketListener l) {
    pairs->add(createPair<String,WebSocketListener>(path,l));
    return this;
}

_WebSocketServerBuilder*_WebSocketServerBuilder::setThreadNum(int num) {
    threadNum = num;
    return this;
}

WebSocketServer _WebSocketServerBuilder::build() {
    WebSocketServer server = createWebSocketServer(addr,httpoption,threadNum);
    ForEveryOne(pair,pairs) {
        server->bind(pair->getKey(),pair->getValue());
    }
    return server;
}

} // namespace obotcha
