#include "json/reader.h"
#include "JsonReader.hpp"
#include "ByteArray.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_JsonReader::_JsonReader(File f) {
    if(!f->exists()) {
        Trigger(InitializeException,"file not exist");
    }

    stream = createFileInputStream(f);
    stream->open();
    mValue = parse();
}

_JsonReader::_JsonReader(String content){
    mValue = parse(content);
}

JsonValue _JsonReader::get() {
    return mValue;
}

JsonValue _JsonReader::parse() {
    ByteArray buff = stream->readAll();

    Json::Reader reader;
    JsonValue value = createJsonValue();
    if(!reader.parse(buff->toString()->toChars(),value->jvalue)){
        return nullptr;
    }
    
    return value;
}

JsonValue _JsonReader::parse(String content) {
    Json::Reader reader;
    JsonValue value = createJsonValue();
    reader.parse(content->toChars(),value->jvalue);
    return value;
}

}