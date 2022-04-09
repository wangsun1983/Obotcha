#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "ArrayList.hpp"
#include "InitializeException.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "BufferedReader.hpp"

namespace obotcha {

_BufferedReader::_BufferedReader(File file):mFileStream(file->getAbsolutePath()->toChars(),std::ifstream::in) {
    if (!file->exists()) {
        Trigger(InitializeException, "file not exists");
    }
    type = ReadFile;
}

_BufferedReader::_BufferedReader(String str) {
    type = ReadContent;
    mData = str->toByteArray();
}

_BufferedReader::_BufferedReader(ByteArray data) {
    type = ReadContent;
    //mStringStream <<data->toValue();
    mData = data;
}

String _BufferedReader::readLine() {    
    std::string s;

    switch(type) {
        case ReadContent:
            if(!isSetStringStream) {
                mStringStream << mData->toString()->toChars();
                isSetStringStream = true;
            }

            if (std::getline(mStringStream, s)) {
                return createString(s);
            }
        break;

        case ReadFile:
            if (std::getline(mFileStream, s)) {
                return createString(s);
            }
        break;
    }
    

    return nullptr;
}

ArrayList<String> _BufferedReader::lines() {
    ArrayList<String> list = createArrayList<String>();
    while(1) {
        String str = readLine();
        if(str != nullptr) {
            list->add(str);
        } else {
            break;
        }
    }

    return list;
}

void _BufferedReader::reset() {
    switch(type) {
        case ReadContent:
            if(isSetStringStream) {
                mStringStream.clear();
                mStringStream.seekg(0, mStringStream.beg);
            }
            break;
        
        case ReadFile:
            mFileStream.seekg(0);
        break;
    } 
}

_BufferedReader::~_BufferedReader() {
    switch(type) {
        case ReadContent:
            //mStringStream.close();
        break;
        
        case ReadFile:
            mFileStream.close();
        break;
    }
    
}

} // namespace obotcha
