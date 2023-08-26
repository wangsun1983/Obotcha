#ifndef __OBOTCHA_PIPE_HPP__
#define __OBOTCHA_PIPE_HPP__

#include <fcntl.h>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(Pipe) {

public:
    static const int ReadChannel;
    static const int WriteChannel;
    static const int kMaxBuffSize;

    _Pipe();
    explicit _Pipe(int);

    ssize_t write(ByteArray data) const;
    ssize_t read(ByteArray buff) const;
    int closeReadChannel();
    int closeWriteChannel();
    int getReadChannel() const;
    int getWriteChannel() const;
    int getMaxSize();
    void close();
    ~_Pipe() override;

private:
    int pipeFd[2];
};

}
#endif
