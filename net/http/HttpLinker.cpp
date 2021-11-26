#include "HttpLinker.hpp"
#include "HttpLinkerManager.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"

namespace obotcha {

_HttpLinker::_HttpLinker(Socket s,int protocol) {
    mParser = createHttpPacketParserImpl();
    mSocket = s;
    mSocketOutput = s->getOutputStream();
    mSession = createHttpSession();
}

void _HttpLinker::close() {
    mSocket->close();
    mParser = nullptr;
}

String _HttpLinker::getClientIp() {
    return mSocket->getInetAddress()->getAddress();
}

int _HttpLinker::pushHttpData(ByteArray array) {
    return mParser->pushHttpData(array);
}

ArrayList<HttpPacket> _HttpLinker::pollHttpPacket() {
    return mParser->doParse();
}

Socket _HttpLinker::getSocket() { return mSocket; }

HttpSession _HttpLinker::getSession() { return mSession; }

} // namespace obotcha