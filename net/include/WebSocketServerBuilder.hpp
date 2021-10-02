#ifndef __OBOTCHA_WEBSOCKET_SERVER_BUILDER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_BUILDER_HPP__

#include <fstream>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <unordered_set>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "WebSocketServer.hpp"

namespace obotcha {

//------------------------WebSocketServer-------------------------
DECLARE_CLASS(WebSocketServerBuilder) {
public:
    _WebSocketServerBuilder();
    _WebSocketServerBuilder* setInetAddr(InetAddress addr);
    _WebSocketServerBuilder* setOption(HttpOption option);
    _WebSocketServerBuilder* addListener(String path,WebSocketListener l);
    _WebSocketServerBuilder* setThreadNum(int);

    WebSocketServer build();
private:
    InetAddress addr;
    int threadNum;
    //WebSocketOption wsoption;
    HttpOption httpoption;
    ArrayList<KeyValuePair<String,WebSocketListener>> pairs;
};

} // namespace obotcha
#endif
