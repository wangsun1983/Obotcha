#ifndef __OBOTCHA_FIFO_PIPE_HPP__
#define __OBOTCHA_FIFO_PIPE_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(FifoPipe) {
public:
    enum Type {
        Read = 0,
        Write,
        AsyncRead,
        AsyncWrite,
    };

    static const int kMaxBuffSize;

    _FifoPipe(String name,int type,int filemode = 0666);
    int init();
    int write(ByteArray data);
    int read(ByteArray buff);
    void close();
    void clear();
    String getName();
    int getChannel();
    ~_FifoPipe();

private:
    int mType;
    int mMode;
    int mFifoId;
    String mPipeName;   
};

}
#endif
