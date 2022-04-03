#include "CRLFDetector.hpp"
#include "HttpText.hpp"

namespace obotcha {

_CRLFDetector::_CRLFDetector() {
    index = 0;
    hasOtherChar = false;
}

bool _CRLFDetector::isEnd(byte &v) {
    return _LocalCheck(v) != CheckStatus::None;
}

bool _CRLFDetector::isOnlyCRLF(byte &v) {
    return _LocalCheck(v) == CheckStatus::OnlyCRLF;
}

int _CRLFDetector::_LocalCheck(byte & v) {
    int ret = None;
    switch(v) {
        case '\r':
            if(index == 1) {
                hasOtherChar = true;
            } else {
                index = 1;
            }
            break;
        
        case '\n':
            if(index == 1) {
                if(hasOtherChar) {
                    ret = ItIsCRLF;
                } else {
                    ret = OnlyCRLF;
                }
                index = 0;
                hasOtherChar = false;
            }
            break;

        default:
            index = 0;
            hasOtherChar = true;
    }

    return ret;

}

}
