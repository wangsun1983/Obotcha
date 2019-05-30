#include "json/reader.h"
#include "JsonReader.hpp"
#include "ByteArray.hpp"

namespace obotcha {

_JsonReader::_JsonReader(File f) {
    stream = createFileInputStream(f);
    stream->open();
    size = f->length();
}

_JsonReader::_JsonReader(String path) {
    File f = createFile(path);
    size = f->length();
    stream = createFileInputStream(path);
    stream->open();
}

JsonValue _JsonReader::parse() {
    ByteArray buff = createByteArray(size);
    stream->read(buff);

    Json::Reader reader;
    JsonValue value = createJsonValue();
    reader.parse(buff->toValue(),value->jvalue);
    return value;
}

}