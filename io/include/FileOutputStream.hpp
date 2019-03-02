#ifndef __FILE_OUTPUT_STREAM_HPP__
#define __FILE_OUTPUT_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"

DECLARE_SIMPLE_CLASS(FileOutputStream) {

public:
    enum FileOpenType {
        Append,
        Trunc
    };

    _FileOutputStream(File file);

    _FileOutputStream(String path);

    bool write(char c);
    
    bool write(char *buffer,int size);

    bool writeString(String s);
    
    bool open(FileOpenType opentype);
    
    void close();

    void flush();

private:
    String mPath;

    std::ofstream fstream;    
};

#endif
