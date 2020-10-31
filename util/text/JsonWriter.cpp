#include "JsonWriter.hpp"

namespace obotcha {

_JsonWriter::_JsonWriter(File f) {
    stream = createFileOutputStream(f);
    stream->open(st(OutputStream)::Trunc);
}

_JsonWriter::_JsonWriter(String path) {
    stream = createFileOutputStream(path);
    stream->open(st(OutputStream)::Trunc);
}

void _JsonWriter::write(JsonValue value) {
    String str = createString(value->jvalue.toStyledString());
    stream->writeString(str);
    stream->flush();
}

void _JsonWriter::close() {
    stream->close();
}

}