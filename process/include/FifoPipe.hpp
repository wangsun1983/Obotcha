#ifndef __OBOTCHA_FIFO_PIPE_HPP__
#define __OBOTCHA_FIFO_PIPE_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

namespace obotcha {


DECLARE_CLASS(FifoPipe) {
public:

    enum Type {
        Read = 0,
        Write,
        AsyncRead,
        AsyncWrite,
    };

    _FifoPipe(String name,int type,int filemode = 0666);

    int init();

    int write(ByteArray data);

    int read(ByteArray buff);

    //int getMaxSize();

    void close();

    void clear();

    String getName();

    ~_FifoPipe();

    int getChannel();

    static const int MaxBuffSize;

private:

    int mType;

    int mMode;

    int fifoId;

    String mPipeName;
   
};

}
#endif
