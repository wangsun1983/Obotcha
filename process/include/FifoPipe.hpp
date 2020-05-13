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

enum FifoPipeType {
    FifoReadPipe = 0,
    FifoWritePipe
};

DECLARE_SIMPLE_CLASS(FifoPipe) {
public:

    _FifoPipe(String name,int type,int filemode);

    _FifoPipe(String,int type);

    int init();

    int writeTo(ByteArray data);

    int readFrom(ByteArray buff);

    int getMaxSize();

    void release();

    void destroy();

    void clean();

    ~_FifoPipe();

private:

    int mType;

    int mMode;

    int fifoId;

    bool isCreated;

    String mPipeName;
   
};

}
#endif
