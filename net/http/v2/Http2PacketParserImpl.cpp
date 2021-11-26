#include "Http2PacketParserImpl.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"

namespace obotcha {

_Http2PacketParserImpl::_Http2PacketParserImpl() {
    mStatus = ShakeHand;
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    mShakeHandParser = createHttp2ShakeHandFrameParser(mRingArray);
}

int _Http2PacketParserImpl::pushHttpData(ByteArray data) {
    mRingArray->push(data);
}

ArrayList<HttpPacket> _Http2PacketParserImpl::doParse() {
    switch(mStatus) {
        case ShakeHand:
        case Preface:{
            ArrayList<HttpPacket> packets = mShakeHandParser->doParser();
            if(packets->size() > 1) {
                LOG(ERROR)<<"HttpV2 parse shake message size > 1";
                return nullptr;
            }

            HttpPacket p = packets->get(0);
            auto header = p->getHeader();
            if(header->getMethod() == st(HttpMethod)::Pri 
                && header->getVersion()->getMajorVer() == 2
                && p->getEntity()->getContent()->toString()->equals("SM\r\n")) {
                mStatus = Comunicated;
                mRingArray->reset();
            }
        }
        break;

        case Comunicated:
        break;
    }

    return nullptr;
}

int _Http2PacketParserImpl::getStatus() {

}

HttpPacket _Http2PacketParserImpl::parseEntireRequest(ByteArray request) {

}

void _Http2PacketParserImpl::reset() {

}

} // namespace obotcha
