#include "JsonWriter.hpp"

namespace obotcha {

_JsonWriter::_JsonWriter(File f) {
    mStream = createFileOutputStream(f);
    mStream->open();
}

_JsonWriter::_JsonWriter(String path) {
    mStream = createFileOutputStream(path);
    mStream->open();
}

_JsonWriter::_JsonWriter(const char* path):_JsonWriter(createString(path)) {
}

void _JsonWriter::write(JsonValue value) {
    mStream->writeString(createString(value->jvalue.toStyledString()));
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