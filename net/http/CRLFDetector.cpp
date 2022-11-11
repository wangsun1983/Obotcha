#include "CRLFDetector.hpp"
#include "HttpText.hpp"

namespace obotcha {

#define NO_FOUND 0
#define R_FOUND  1

_CRLFDetector::_CRLFDetector() {
    mState = NO_FOUND;
    mHasOtherChar = false;
}

bool _CRLFDetector::isEnd(byte &v) {
    return check(v) != CheckStatus::None;
}

bool _CRLFDetector::isOnlyCRLF(byte &v) {
    return check(v) == CheckStatus::OnlyCRLF;
}

int _CRLFDetector::check(byte & v) {
    int ret = None;
    switch(v) {
        case '\r':
            (mState == R_FOUND)?mHasOtherChar = true:mState = R_FOUND;
            break;
        
        case '\n':
            if(mState == R_FOUND) {
                ret = (mHasOtherChar)?ItIsCRLF:OnlyCRLF;
                mState = NO_FOUND;
                mHasOtherChar = false;
            }
            break;

        default:
            mState = NO_FOUND;
            mHasOtherChar = true;
    }
    return ret;
}

}
