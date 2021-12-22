#include "HttpPacketParser.hpp"

namespace obotcha {

int _HttpPacketParser::getStatus() {
    return mStatus;
}
    
void _HttpPacketParser::setStatus(int s) {
    mStatus = s;
}

}
