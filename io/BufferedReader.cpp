#include <iostream>
#include <sstream>

#include "BufferedReader.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_BufferedReader::_BufferedReader(File file):mFileStream(file->getAbsolutePath()->toChars(),std::ifstream::in) {
    Panic(!file->exists(),InitializeException, "file not exists")
    mType = _BufferedReader::Type::Document;
}

_BufferedReader::_BufferedReader(String str) {
    mType = _BufferedReader::Type::Content;
    mStringStream << str->toChars();
}

_BufferedReader::_BufferedReader(ByteArray data) {
    mType = _BufferedReader::Type::Content;
    mStringStream << data->toValue() <<'\0';
}

String _BufferedReader::readLine() {
    std::string s;
    if(mType == _BufferedReader::Type::Content) {
        std::getline(mStringStream, s);
    } else if (mType == _BufferedReader::Type::Document) {
        std::getline(mFileStream, s);
    }
    return s.empty()?nullptr:createString(s);
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
        case _BufferedReader::Type::Content:
            mStringStream.clear();
            mStringStream.seekg(0, mStringStream.beg);
        break;

        case _BufferedReader::Type::Document:
            mFileStream.seekg(0);
        break;
    }
}

} // namespace obotcha
