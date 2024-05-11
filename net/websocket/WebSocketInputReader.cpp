#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi00Parser.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi07Parser.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi08Parser.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketInputReader.hpp"
#include "Log.hpp"

namespace obotcha {

_WebSocketInputReader::_WebSocketInputReader(int version,
                                            [[maybe_unused]]_WebSocketProtocol::Model model) {
    switch (version) {
        case 0: {
            mParser = WebSocketHybi00Parser::New();
            break;
        }

        case 7: {
            mParser = WebSocketHybi07Parser::New();
            break;
        }

        case 8: {
            mParser = WebSocketHybi08Parser::New();
            break;
        }

        case 13: {
            mParser = WebSocketHybi13Parser::New();
            break;
        }

        default:
            LOG(ERROR)<<"WebSocket Protocol Not Support,Version is "<<version;
        break;
    }
}

void _WebSocketInputReader::push(ByteArray data) {
    mParser->pushParseData(data);
}

ArrayList<WebSocketFrame> _WebSocketInputReader::pull() {
    return mParser->doParse();
}

WebSocketParser _WebSocketInputReader::getParser() {
    return mParser;
}

}
