#ifndef __OBOTCHA_JSON_READER_H__
#define __OBOTCHA_JSON_READER_H__

#include "Object.hpp"
#include "String.hpp"
#include "JsonValue.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(JsonReader) {
public:
    explicit _JsonReader() = default;
    sp<_JsonReader> loadContent(String);
    sp<_JsonReader> loadFile(File);
    JsonValue get();
private:
    String mContent;
    JsonValue mValue;
    JsonValue parse(File) const;
    JsonValue parse(String) const;
};

} // namespace obotcha
#endif