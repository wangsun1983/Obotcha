#ifndef __OBOTCHA_PRINT_STREAM_HPP__
#define __OBOTCHA_PRINT_STREAM_HPP__

#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "OutputStream.hpp"
#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(PrintStream) IMPLEMENTS(OutputStream) {

public:
    _PrintStream(File file);

    _PrintStream(String path);

    _PrintStream();

    long write(char c);
    
    long write(ByteArray);

    long write(ByteArray buff,long size);

    void setOutPath(String path);

    bool open();
    
    void close();

    void flush();

    void println(String s);

    void print(String s);

    void newline();

private:
    String mPath;
    
    bool isDefaultOut;
    
    std::ofstream fstream;
};

}
#endif
