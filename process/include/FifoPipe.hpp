#ifndef __FIFO_PIPE_HPP__
#define __FIFO_PIPE_HPP__

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
    _FifoPipe(String,int type);

    bool init();

    bool writeTo(ByteArray data);

    int readFrom(ByteArray buff);

    ~_FifoPipe();

private:

    int mType;

    int fifoId;

    bool isCreated;

    String mPipeName;
   
};

}
#endif
