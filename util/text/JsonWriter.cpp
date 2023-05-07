#include "JsonWriter.hpp"

namespace obotcha {

_JsonWriter::_JsonWriter(File f) {
    stream = createFileOutputStream(f);
    stream->open();
}

_JsonWriter::_JsonWriter(String path) {
    stream = createFileOutputStream(path);
    stream->open();
}

_JsonWriter::_JsonWriter(const char *path) {
    stream = createFileOutputStream(path);
    stream->open();
}

void _JsonWriter::write(JsonValue value) {
    stream->writeString(createString(value->jvalue.toStyledString()));
    stream->flush();
}

void _JsonWriter::close() { 
    stream->close(); 
}

} // namespace obotcha