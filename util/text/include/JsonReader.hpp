#ifndef __OBOTCHA_JSON_READER_H__
#define __OBOTCHA_JSON_READER_H__

#include "Boolean.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"

#include "JsonValue.hpp"

#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(JsonReader) {
public:
    explicit _JsonReader(File f);

    explicit _JsonReader(String content);

    JsonValue get();

private:
    String mContent;

    JsonValue mValue;

    JsonValue parse(File) const;

    JsonValue parse(String) const;
};

} // namespace obotcha
#endif