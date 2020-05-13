#ifndef __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__
#define __OBOTCHA_WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "ZipFileStream.hpp"
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

DECLARE_SIMPLE_CLASS(WebSocketPermessageDeflate) {

public:
    _WebSocketPermessageDeflate();
    bool fit(ArrayList<String>);
    void init();

    ByteArray compress(ByteArray);
    ByteArray decompress(ByteArray);

    int getServerMaxWindowBits();
    int getClientMaxWindowBits();
    
private:
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
