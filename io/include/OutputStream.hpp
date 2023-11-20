#ifndef __OBOTCHA_OUTPUT_STREAM_HPP__
#define __OBOTCHA_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "IO.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

DECLARE_CLASS(OutputStream) {
  public:
    virtual long write(char c) { return -1; }

    virtual long write(ByteArray buff) = 0;
    virtual long write(ByteArray buff, uint64_t start) = 0;
    virtual long write(ByteArray buff, uint64_t start, uint64_t len) = 0;

    virtual bool open() { return false; }
    virtual bool open(int options) { return false; }
    virtual void close() {/*Intentionally unimplemented...*/}
    virtual void flush() {/*Intentionally unimplemented...*/}

    virtual void setAsync(bool,sp<_AsyncOutputChannelPool> pool = nullptr) {
      /*Intentionally unimplemented...*/
    }
};

} // namespace obotcha
#endif
