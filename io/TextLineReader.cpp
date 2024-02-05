/**
 * @file TextLineReader.cpp
 * @brief  Reads a line of text from a character-input stream.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */

#include <iostream>
#include <sstream>

#include "TextLineReader.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_TextLineReader::_TextLineReader(File file):mFileStream(file->getAbsolutePath()->toChars(),std::ifstream::in) {
    Panic(!file->exists(),InitializeException, "file not exists")
    mType = _TextLineReader::Type::Document;
}

_TextLineReader::_TextLineReader(String str) {
    mType = _TextLineReader::Type::Content;
    mStringStream << str->toChars();
}

_TextLineReader::_TextLineReader(ByteArray data) {
    mType = _TextLineReader::Type::Content;
    mStringStream << data->toValue() <<'\0';
}

String _TextLineReader::readLine() {
    std::string s;
    if(mType == _TextLineReader::Type::Content) {
        std::getline(mStringStream, s);
    } else if (mType == _TextLineReader::Type::Document) {
        std::getline(mFileStream, s);
    }
    return s.empty()?nullptr:createString(s);
}

ArrayList<String> _TextLineReader::lines() {
    ArrayList<String> list = createArrayList<String>();
    String str = nullptr;
    while((str = readLine())!= nullptr) {
        list->add(str);
    }
    return list;
}

void _TextLineReader::reset() {
    switch(mType) {
        case _TextLineReader::Type::Content:
            mStringStream.clear();
            mStringStream.seekg(0, mStringStream.beg);
        break;

        case _TextLineReader::Type::Document:
            mFileStream.clear();
            mFileStream.seekg(0);
        break;
    }
}

} // namespace obotcha
