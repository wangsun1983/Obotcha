#include "WebSocketPermessageDeflate.hpp"

namespace obotcha {

#define TAG "WebSocketPermessageDeflate"

/// Default value for server_max_window_bits as defined by RFC 7692
//static uint8_t const DEFAULT_SERVER_MAX_WINDOW_BITS = 15;
const uint8_t st(WebSocketPermessageDeflate)::kDefaultServerMaxWindowBits = 15;

/// Minimum value for server_max_window_bits as defined by RFC 7692
/**
 * NOTE: A value of 8 is not actually supported by zlib, the deflate
 * library that WebSocket++ uses. To preserve backwards compatibility
 * with RFC 7692 and previous versions of the library a value of 8
 * is accepted by the library but will always be negotiated as 9.
 */
//static uint8_t const MIN_SERVER_MAX_WINDOW_BITS = 8;
const uint8_t st(WebSocketPermessageDeflate)::kMinServerMaxWindowBits = 8;

/// Maximum value for server_max_window_bits as defined by RFC 7692
//static uint8_t const MAX_SERVER_MAX_WINDOW_BITS = 15;
const uint8_t st(WebSocketPermessageDeflate)::kMaxServerMaxWindowBits = 15;

/// Default value for client_max_window_bits as defined by RFC 7692
//static uint8_t const DEFAULT_CLIENT_MAX_WINDOW_BITS = 15;
const uint8_t st(WebSocketPermessageDeflate)::kDefaultClientMaxWindowBits = 15;

/// Minimum value for client_max_window_bits as defined by RFC 7692
/**
 * NOTE: A value of 8 is not actually supported by zlib, the deflate
 * library that WebSocket++ uses. To preserve backwards compatibility
 * with RFC 7692 and previous versions of the library a value of 8
 * is accepted by the library but will always be negotiated as 9.
 */
//static uint8_t const MIN_CLIENT_MAX_WINDOW_BITS = 8;
const uint8_t st(WebSocketPermessageDeflate)::kMinClientMaxWindowBits = 8;

/// Maximum value for client_max_window_bits as defined by RFC 7692
//static uint8_t const MAX_CLIENT_MAX_WINDOW_BITS = 15;
const uint8_t st(WebSocketPermessageDeflate)::kMaxClientMaxWindowBits = 15;

_WebSocketPermessageDeflate::_WebSocketPermessageDeflate():mServerNoContextTakeover(false),
                                                           mClientNoContextTakeover(false),
                                                           mServerMaxWindowBits(15),
                                                           mClientMaxWindowBits(15),
                                                           mServerMaxWindowBitsMode(WebSocketModeAccept),
                                                           mClientMaxWindowBitsMode(WebSocketModeAccept) {
    mZip = createZipMemoryStream();
}

bool _WebSocketPermessageDeflate::fit(ArrayList<String> l) {
    ArrayListIterator<String>iterator = l->getIterator();
    bool isPermessageDeflat = false;
    while(iterator->hasValue()) {
        String v = iterator->getValue();
        if(v->equalsIgnoreCase("permessage-deflate")) {
            isPermessageDeflat = true;
        }

        if(isPermessageDeflat) {
            goto next;
        }

        if(v->equalsIgnoreCase("server_no_context_takeover")) {
            mServerNoContextTakeover = true;
        } else if(v->equalsIgnoreCase("client_no_context_takeover")) {
            mClientNoContextTakeover = true;
        } else if(v->startsWithIgnoreCase("server_max_window_bits")) {
            ArrayList<String> values = v->split("=");
            if(values == nullptr ||values->size() != 2) {
                goto next;
            }
            setServerMaxWindowBits(values->get(1)->toBasicInt());
        } else if(v->startsWithIgnoreCase("client_max_window_bits")) {
            ArrayList<String> values = v->split("=");
            if(values == nullptr ||values->size() != 2) {
                goto next;
            }
            setClientMaxWindowBits(values->get(1)->toBasicInt());
        }
next:
        iterator->next();   
    }

    return isPermessageDeflat;
}

void _WebSocketPermessageDeflate::setServerMaxWindowBits(int bits) {
    if (bits < kMinServerMaxWindowBits || bits > kMaxServerMaxWindowBits) {
        mServerMaxWindowBits = kDefaultServerMaxWindowBits;
        return;
    }

    switch(mServerMaxWindowBitsMode) {
        case WebSocketModeAccept:{
            mServerMaxWindowBitsMode = bits;
            break;
        }
        case WebSocketModeDecline: {
            mServerMaxWindowBitsMode = kDefaultServerMaxWindowBits;
            break;
        }
        case WebSocketModeLargest: {
            mServerMaxWindowBitsMode = std::min(bits,mServerMaxWindowBitsMode);
            break;
        }
        case WebSocketModeSmallest: {
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
        case WebSocketModeAccept:{
            mClientMaxWindowBits = bits;
            break;
        }
        case WebSocketModeDecline: {
            mClientMaxWindowBits = kDefaultClientMaxWindowBits;
            break;
        }
        case WebSocketModeLargest: {
            mClientMaxWindowBits = std::min(bits,mClientMaxWindowBits);
            break;
        }
        case WebSocketModeSmallest: {
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

int _WebSocketPermessageDeflate::getServerMaxWindowBits() {
    return mServerMaxWindowBits;
}

int _WebSocketPermessageDeflate::getClientMaxWindowBits() {
    return mClientMaxWindowBits;
}

}

