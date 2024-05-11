#ifndef __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__
#define __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "ZipMemoryStream.hpp"
#include "WebSocket.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketPermessageDeflate) {

public:
    _WebSocketPermessageDeflate() = default;
    bool fit(ArrayList<String>);
    void init();

    ByteArray compress(ByteArray);
    ByteArray decompress(ByteArray);

    int getServerMaxWindowBits() const;
    int getClientMaxWindowBits() const;
    
private:
    static const uint8_t kDefaultServerMaxWindowBits;
    static const uint8_t kMinServerMaxWindowBits;
    static const uint8_t kMaxServerMaxWindowBits;
    static const uint8_t kDefaultClientMaxWindowBits;
    static const uint8_t kMinClientMaxWindowBits;
    static const uint8_t kMaxClientMaxWindowBits;

    void setServerMaxWindowBits(int);
    void setClientMaxWindowBits(int);
    bool mServerNoContextTakeover = false;
    bool mClientNoContextTakeover = false;
    int mServerMaxWindowBits = kMaxServerMaxWindowBits;
    int mClientMaxWindowBits = kMaxClientMaxWindowBits;
    int mServerMaxWindowBitsMode = _WebSocket::WindowBitsMode::Accept;
    int mClientMaxWindowBitsMode = _WebSocket::WindowBitsMode::Accept;
    ZipMemoryStream mZip = ZipMemoryStream::New();
};

}
#endif
