#include "CRLFDetector.hpp"
#include "HttpText.hpp"

namespace obotcha {

const char *_CRLFDetector::CRLF = "\r\n";//st(HttpText)::CRLF->toChars();

_CRLFDetector::_CRLFDetector() {
    index = 0;
}

bool _CRLFDetector::isEnd(byte &v) {
    if(CRLF[index] == v) {
        if(index == 0) {
            index++;
        } else {
            index = 0;
            return true;
        }
    } else {
        index = 0;
    }

    return false;
}

}
