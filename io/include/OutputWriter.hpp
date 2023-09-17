#ifndef __OBOTCHA_OUTPUT_WRITER_HPP__
#define __OBOTCHA_OUTPUT_WRITER_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(OutputWriter) {
public:
    virtual ssize_t write(ByteArray,uint64_t start = 0,uint64_t length = 0) = 0;
};

} // namespace obotcha

#endif
