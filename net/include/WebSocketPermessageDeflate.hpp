#ifndef __WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__
#define __WEB_SOCKET_PERMESSAGE_DEFLATE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

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
    bool set(ArrayList<String>);
    void init();
    
private:
    void setServerMaxWindowBits(int);
    void setClientMaxWindowBits(int);
    bool mServerNoContextTakeover;
    bool mClientNoContextTakeover;
    int mServerMaxWindowBits;
    int mClientMaxWindowBits;
    int mServerMaxWindowBitsMode;
    int mClientMaxWindowBitsMode;
};

}
#endif
