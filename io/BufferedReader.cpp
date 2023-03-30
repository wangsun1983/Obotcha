#include <iostream>
#include <sstream>

#include "BufferedReader.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_BufferedReader::_BufferedReader(File file):mFileStream(file->getAbsolutePath()->toChars(),std::ifstream::in) {
    Panic(!file->exists(),InitializeException, "file not exists");
    mType = Document;
}

_BufferedReader::_BufferedReader(String str) {
    mType = Content;
    mStringStream << str->toChars();
}

_BufferedReader::_BufferedReader(ByteArray data) {
    mType = Content;
    mStringStream << data->toValue() <<'\0';
}

String _BufferedReader::readLine() {
    std::string s;
    switch(mType) {
        case Content:
            if (std::getline(mStringStream, s)) {
                return createString(s);
            }
        break;

        case Document:
            if (std::getline(mFileStream, s)) {
                return createString(s);
            }
        break;
    }
    return nullptr;
}

ArrayList<String> _BufferedReader::lines() {
    ArrayList<String> list = createArrayList<String>();
    String str = nullptr;
    while((str = readLine())!= nullptr) {
        list->add(str);
    }
    return list;
}

void _BufferedReader::reset() {
    switch(mType) {
        case Content:
            mStringStream.clear();
            mStringStream.seekg(0, mStringStream.beg);
        break;

        case Document:
            mFileStream.seekg(0);
        break;
    }
}

} // namespace obotcha
