#ifndef __FILE_INPUT_STREAM_HPP__
#define __FILE_INPUT_STREAM_HPP__

#include <fstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"

DECLARE_SIMPLE_CLASS(FileInputStream) IMPLEMENTS(InputStream) {
public:

    _FileInputStream(File f);
    
    _FileInputStream(String path);

    int read();

    int read(char *buffer,int size);

    bool open();

    void close();

    String readLine();

private:
    String mPath;

    std::ifstream fstream;     
};

#endif
