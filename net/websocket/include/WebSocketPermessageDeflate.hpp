#ifndef __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__
#define __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "ZipMemoryStream.hpp"

namespace obotcha {

enum WebSocketMode {
    /// Accept any value the remote endpoint offers
    WebSocketModeAccept = 1,
    /// Decline any value the remote endpoint offers. Insist on defaults.
    WebSocketModeDecline,
    /// Use the largest value common to both offers
    WebSocketModeLargest,
    /// Use the smallest value common to both offers
    WebSocketModeSmallest
};

DECLARE_CLASS(WebSocketPermessageDeflate) {

public:
    _WebSocketPermessageDeflate();
    bool fit(ArrayList<String>);
    void init();

    ByteArray compress(ByteArray);
    ByteArray decompress(ByteArray);

    int getServerMaxWindowBits();
    int getClientMaxWindowBits();
    
private:
    static const uint8_t kDefaultServerMaxWindowBits;
    static const uint8_t kMinServerMaxWindowBits;
    static const uint8_t kMaxServerMaxWindowBits;
    static const uint8_t kDefaultClientMaxWindowBits;
    static const uint8_t kMinClientMaxWindowBits;
    static const uint8_t kMaxClientMaxWindowBits;

    void setServerMaxWindowBits(int);
    void setClientMaxWindowBits(int);
    bool mServerNoContextTakeover;
    bool mClientNoContextTakeover;
    int mServerMaxWindowBits;
    int mClientMaxWindowBits;
    int mServerMaxWindowBitsMode;
    int mClientMaxWindowBitsMode;

    ZipMemoryStream mZip;
};

}
#endif
