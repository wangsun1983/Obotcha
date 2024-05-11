#include "JsonWriter.hpp"

namespace obotcha {

_JsonWriter::_JsonWriter(File f) {
    mStream = FileOutputStream::New(f);
    mStream->open();
}

_JsonWriter::_JsonWriter(String path) {
    mStream = FileOutputStream::New(path);
    mStream->open();
}

_JsonWriter::_JsonWriter(const char* path):_JsonWriter(String::New(path)) {
}

void _JsonWriter::write(JsonValue value) {
    mStream->writeString(String::New(value->jvalue.toStyledString()));
    mStream->flush();
}

void _JsonWriter::close() {
    if(!isClosed) {
        mStream->close();
        isClosed = true;
    }
}

_JsonWriter::~_JsonWriter() {
    close();
}

} // namespace obotcha