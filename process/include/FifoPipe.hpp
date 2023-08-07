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
    ssize_t write(ByteArray data);
    ssize_t read(ByteArray buff) const;
    void close();
    void clear();
    String getName() const;
    int getChannel() const;
    ~_FifoPipe();

private:
    int mType;
    int mMode;
    int mFifoId;
    String mPipeName;   
};

}
#endif
