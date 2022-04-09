#ifndef __OBOTCHA_BUFFERED_READER_HPP__
#define __OBOTCHA_BUFFERED_READER_HPP__

#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "FileInputStream.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(BufferedReader) {

public:
    _BufferedReader(File);

    _BufferedReader(String);

    _BufferedReader(ByteArray); 

    String readLine();

    ArrayList<String> lines();

    void reset();

    ~_BufferedReader();

private:
    enum type {
        ReadFile = 0,
        ReadContent
    };

    bool isSetStringStream = false;
    std::stringstream mStringStream;
    std::ifstream mFileStream;
    ByteArray mData;

    int type;
};

} // namespace obotcha
#endif
