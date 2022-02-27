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

private:
    int index;
    static const char *CRLF;
};

}

#endif