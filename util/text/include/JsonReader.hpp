#ifndef __OBOTCHA_JSON_READER_H__
#define __OBOTCHA_JSON_READER_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Float.hpp"
#include "Long.hpp"

#include "JsonValue.hpp"

#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(JsonReader) {
public:
    _JsonReader(File f);

    _JsonReader(String content);

    JsonValue get();

private:
    String mContent;

    JsonValue mValue;

    JsonValue parse(File);

    JsonValue parse(String);
};

}
#endif