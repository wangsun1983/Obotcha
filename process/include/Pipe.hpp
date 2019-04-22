#ifndef __PIPE_HPP__
#define __PIPE_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

namespace obotcha {

enum PipeType {
    FirstPipe = 0,
    SecondPipe
};

DECLARE_SIMPLE_CLASS(Pipe) {
public:
    _Pipe();

    bool init();

    bool writeTo(int type,ByteArray data);

    int readFrom(int type,ByteArray buff);

    ~_Pipe();

private:

    int pipeFd[2];

    bool isCreated;
   
};

}
#endif
