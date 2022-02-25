#include "CRLFDetector.hpp"

namespace obotcha {

_CRLFDetector::_CRLFDetector() {
    index = 0;
}

bool _CRLFDetector::isEnd(byte &v) {
    if(v == '\r' && index == 0) {
        index = 1;
    } else if(v == '\n' && index == 1) {
        index = 0;
        return true;
    } else {
        index = 0;
    }

    return false;
}

}
