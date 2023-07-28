#include "CRLFDetector.hpp"
#include "HttpText.hpp"

namespace obotcha {

const int _CRLFDetector::kNotFound = 0;
const int _CRLFDetector::kFound = 1;

bool _CRLFDetector::isEnd(const byte &v) {
    return check(v) != CheckStatus::None;
}

bool _CRLFDetector::isOnlyCRLF(const byte &v) {
    return check(v) == CheckStatus::OnlyCRLF;
}

int _CRLFDetector::check(const byte & v) {
    int ret = None;
    switch(v) {
        case '\r':
            (mState == kFound)?mHasOtherChar = true:mState = kFound;
            break;
        
        case '\n':
            if(mState == kFound) {
                ret = mHasOtherChar?ItIsCRLF:OnlyCRLF;
                mState = kNotFound;
                mHasOtherChar = false;
            }
            break;

        default:
            mState = kNotFound;
            mHasOtherChar = true;
    }
    return ret;
}

}
