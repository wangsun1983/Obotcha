#ifndef __OBOTCHA_FILE_NODE_READER_HPP__
#define __OBOTCHA_FILE_NODE_READER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileNodeReader) {
public:
    _FileNodeReader(String path,int buffsize = 128);

    int readInt();

    bool readBoolean();

    long readLong();

    String readString();

    String getPath();

    ~_FileNodeReader();

private:
	int mSize;

	String mPath;

	int mFd;
};

}
#endif
