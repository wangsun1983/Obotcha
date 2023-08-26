#include "WebSocketPermessageDeflate.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

/// Default value for server_max_window_bits as defined by RFC 7692
const uint8_t st(WebSocketPermessageDeflate)::kDefaultServerMaxWindowBits = 15;

/// Minimum value for server_max_window_bits as defined by RFC 7692
/**
 * NOTE: A value of 8 is not actually supported by zlib, the deflate
 * library that WebSocket++ uses. To preserve backwards compatibility
 * with RFC 7692 and previous versions of the library a value of 8
 * is accepted by the library but will always be negotiated as 9.
 */
const uint8_t st(WebSocketPermessageDeflate)::kMinServerMaxWindowBits = 8;

/// Maximum value for server_max_window_bits as defined by RFC 7692
const uint8_t st(WebSocketPermessageDeflate)::kMaxServerMaxWindowBits = 15;

/// Default value for client_max_window_bits as defined by RFC 7692
const uint8_t st(WebSocketPermessageDeflate)::kDefaultClientMaxWindowBits = 15;

/// Minimum value for client_max_window_bits as defined by RFC 7692
/**
 * NOTE: A value of 8 is not actually supported by zlib, the deflate
 * library that WebSocket++ uses. To preserve backwards compatibility
 * with RFC 7692 and previous versions of the library a value of 8
 * is accepted by the library but will always be negotiated as 9.
 */
const uint8_t st(WebSocketPermessageDeflate)::kMinClientMaxWindowBits = 8;

/// Maximum value for client_max_window_bits as defined by RFC 7692
const uint8_t st(WebSocketPermessageDeflate)::kMaxClientMaxWindowBits = 15;

bool _WebSocketPermessageDeflate::fit(ArrayList<String> l) {
    bool isPermessageDeflat = false;
    ForEveryOne(v,l) {
        if(v->equalsIgnoreCase("permessage-deflate")) {
            isPermessageDeflat = true;
        }

        if(isPermessageDeflat) {
            continue;
        }

        if(v->equalsIgnoreCase("server_no_context_takeover")) {
            mServerNoContextTakeover = true;
        } else if(v->equalsIgnoreCase("client_no_context_takeover")) {
            mClientNoContextTakeover = true;
        } else if(v->startsWithIgnoreCase("server_max_window_bits")) {
            ArrayList<String> values = v->split("=");
            if(values == nullptr ||values->size() != 2) {
                continue;
            }
            setServerMaxWindowBits(values->get(1)->toBasicInt());
        } else if(v->startsWithIgnoreCase("client_max_window_bits")) {
            ArrayList<String> values = v->split("=");
            if(values == nullptr ||values->size() != 2) {
                continue;
            }
            setClientMaxWindowBits(values->get(1)->toBasicInt());
        }  
    }

    return isPermessageDeflat;
}

void _WebSocketPermessageDeflate::setServerMaxWindowBits(int bits) {
    if (bits < kMinServerMaxWindowBits || bits > kMaxServerMaxWindowBits) {
        mServerMaxWindowBits = kDefaultServerMaxWindowBits;
        return;
    }

    switch(mServerMaxWindowBitsMode) {
        case st(WebSocket)::WindowBitsMode::Accept:{
            mServerMaxWindowBitsMode = bits;
            break;
        }
        case st(WebSocket)::WindowBitsMode::Decline: {
            mServerMaxWindowBitsMode = kDefaultServerMaxWindowBits;
            break;
        }
        case st(WebSocket)::WindowBitsMode::Largest: {
            mServerMaxWindowBitsMode = std::min(bits,mServerMaxWindowBitsMode);
            break;
        }
        case st(WebSocket)::WindowBitsMode::Smallest: {
            mServerMaxWindowBitsMode = kMinServerMaxWindowBits;
            break;
        }

        default:
            mServerMaxWindowBitsMode = kDefaultServerMaxWindowBits;
    }

    // See note in doc comment
    if (mServerMaxWindowBitsMode == 8) {
        mServerMaxWindowBitsMode = 9;
    }

    //TODO update mZip
}

void _WebSocketPermessageDeflate::setClientMaxWindowBits(int bits) {
    if (bits < kMinServerMaxWindowBits ||bits > kMaxServerMaxWindowBits) {
        mClientMaxWindowBits = kDefaultClientMaxWindowBits;
        return;
    }

    switch(mClientMaxWindowBitsMode) {
        case st(WebSocket)::WindowBitsMode::Accept:{
            mClientMaxWindowBits = bits;
            break;
        }
        case st(WebSocket)::WindowBitsMode::Decline: {
            mClientMaxWindowBits = kDefaultClientMaxWindowBits;
            break;
        }
        case st(WebSocket)::WindowBitsMode::Largest: {
            mClientMaxWindowBits = std::min(bits,mClientMaxWindowBits);
            break;
        }
        case st(WebSocket)::WindowBitsMode::Smallest: {
            mClientMaxWindowBits = kMinClientMaxWindowBits;
            break;
        }

        default:
        mClientMaxWindowBits = kDefaultClientMaxWindowBits;
    }

    // See note in doc comment
    if (mClientMaxWindowBits == 8) {
        mClientMaxWindowBits = 9;
    }

    //TODO update mZip
}

void _WebSocketPermessageDeflate::init() {
    //TODO
}

ByteArray _WebSocketPermessageDeflate::compress(ByteArray b) {
    return mZip->compress(b);
}

ByteArray _WebSocketPermessageDeflate::decompress(ByteArray b) {
    return mZip->decompress(b);
}

int _WebSocketPermessageDeflate::getServerMaxWindowBits() const {
    return mServerMaxWindowBits;
}

int _WebSocketPermessageDeflate::getClientMaxWindowBits() const {
    return mClientMaxWindowBits;
}

}

