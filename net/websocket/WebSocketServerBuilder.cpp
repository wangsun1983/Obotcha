#include "WebSocketServerBuilder.hpp"
#include "Enviroment.hpp"
#include "Definations.hpp"

namespace obotcha {

_WebSocketServerBuilder::_WebSocketServerBuilder(){
    pairs = createArrayList<Pair<String,WebSocketListener>>();
    threadNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
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
    WebSocketServer server = createWebSocketServer(threadNum);
    server->mAddress = addr;
    server->mHttpOption = httpoption;
    auto iterator = pairs->getIterator();
    while(iterator->hasValue()) {
        server->bind(iterator->getValue()->getKey(),iterator->getValue()->getValue());
        iterator->next();
    }
    return server;
}

} // namespace obotcha
