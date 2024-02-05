#ifndef __OBOTCHA_TEXT_LINE_READER_HPP__
#define __OBOTCHA_TEXT_LINE_READER_HPP__

#include <fstream>

#include "Object.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(TextLineReader) {

public:
    explicit _TextLineReader(File);
    explicit _TextLineReader(String);
    explicit _TextLineReader(ByteArray); 
    String readLine();
    ArrayList<String> lines();
    void reset();

private:
    enum class Type {
        Document = 0,
        Content
    };

    std::stringstream mStringStream;
    std::ifstream mFileStream;
    _TextLineReader::Type mType;
};

} // namespace obotcha
#endif
