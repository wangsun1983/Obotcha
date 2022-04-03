#ifndef __OBOTCHA_CRLF_DETECTOR_HPP__
#define __OBOTCHA_CRLF_DETECTOR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(CRLFDetector) {
public:
    _CRLFDetector();
    bool isEnd(byte &);
    bool isOnlyCRLF(byte &);

private:
    int index;
    bool hasOtherChar;
    
    enum CheckStatus{
        ItIsCRLF = 0,
        OnlyCRLF,
        None,
    };

    int _LocalCheck(byte &);
};

}

#endif