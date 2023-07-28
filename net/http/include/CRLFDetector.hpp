#ifndef __OBOTCHA_CRLF_DETECTOR_HPP__
#define __OBOTCHA_CRLF_DETECTOR_HPP__

#include "Object.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(CRLFDetector) {
public:
    static const int kNotFound;
    static const int kFound;

    _CRLFDetector() = default;;
    bool isEnd(const byte &);
    bool isOnlyCRLF(const byte &);

private:
    int mState = kNotFound;
    bool mHasOtherChar = false;
    
    enum CheckStatus{
        ItIsCRLF = 0,
        OnlyCRLF,
        None,
    };

    int check(const byte &);
};



}

#endif