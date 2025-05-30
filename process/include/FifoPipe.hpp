#ifndef __OBOTCHA_FIFO_PIPE_HPP__
#define __OBOTCHA_FIFO_PIPE_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(FifoPipe) {
public:
    enum class Type {
        Read = 0,
        Write,
        AsyncRead,
        AsyncWrite,
    };

    static const int kMaxBuffSize;

    _FifoPipe(String name,Type type,int filemode = 0666);
    ssize_t write(ByteArray data) const;
    ssize_t read(ByteArray buff) const;
    void close();
    String getName() const;
    int getChannel() const;
    ~_FifoPipe() override;

    static int Create(String name);
    static int Clear(String name);

private:
    Type mType;
    int mMode;
    int mFifoId;
    String mPipeName;   
};

}
#endif
