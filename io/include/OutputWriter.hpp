#ifndef __OBOTCHA_OUTPUT_WRITER_HPP__
#define __OBOTCHA_OUTPUT_WRITER_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(OutputWriter) {
public:
    virtual int write(ByteArray,int start = 0,int length = 0) = 0;
};

} // namespace obotcha

#endif
