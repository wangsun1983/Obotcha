#ifndef __OBOTCHA_BUFFERED_READER_HPP__
#define __OBOTCHA_BUFFERED_READER_HPP__

#include <fstream>

#include "Object.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(BufferedReader) {

public:
    explicit _BufferedReader(File);
    explicit _BufferedReader(String);
    explicit _BufferedReader(ByteArray); 
    String readLine();
    ArrayList<String> lines();
    void reset();

private:
    enum type {
        Document = 0,
        Content
    };

    std::stringstream mStringStream;
    std::ifstream mFileStream;
    int mType;
};

} // namespace obotcha
#endif
