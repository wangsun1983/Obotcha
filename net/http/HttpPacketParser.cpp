#include "HttpPacketParser.hpp"

namespace obotcha {

int _HttpPacketParser::getStatus() {
    printf("parser get status is %d \n",mStatus);
    return mStatus;
}
    
void _HttpPacketParser::setStatus(int s) {
    mStatus = s;
}

}
