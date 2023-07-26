#include "json/reader.h"

#include "ByteArray.hpp"
#include "FileInputStream.hpp"
#include "InitializeException.hpp"
#include "JsonReader.hpp"

namespace obotcha {

_JsonReader::_JsonReader(File f) {
    if (!f->exists()) {
        Trigger(InitializeException, "file not exist")
    }

    mValue = parse(f);
}

_JsonReader::_JsonReader(String content) { 
    mValue = parse(content); 
}

JsonValue _JsonReader::get() { 
    return mValue; 
}

JsonValue _JsonReader::parse(File f) {
    auto stream = createFileInputStream(f);
    stream->open();
    ByteArray buff = stream->readAll();
    stream->close();
    return parse(buff->toString());
}

JsonValue _JsonReader::parse(String content) {
    Json::Reader reader;
    JsonValue value = createJsonValue();
    if (!reader.parse(content->toChars(), value->jvalue)) {
        return nullptr;
    }

    if (value->jvalue.empty() || value->jvalue.isNull()) {
        return nullptr;
    }

    return value;
}

} // namespace obotcha