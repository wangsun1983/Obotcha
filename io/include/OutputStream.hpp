#ifndef __OBOTCHA_OUTPUT_STREAM_HPP__
#define __OBOTCHA_OUTPUT_STREAM_HPP__

#include "ByteArray.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

DECLARE_CLASS(OutputStream) {
  public:
    virtual long write(char c) { return -1; }

    virtual long write(ByteArray buff) = 0;

    virtual long write(ByteArray buff, int start) = 0;

    virtual long write(ByteArray buff, int start, int len) = 0;

    virtual bool open() { return false; }

    virtual bool open(int) { return false; }

    virtual void close() {}

    virtual void flush() {}

    virtual void setAsync(bool,sp<_AsyncOutputChannelPool> pool = nullptr) {}

    enum FileOpenType { Append, Trunc };
};

} // namespace obotcha
#endif
