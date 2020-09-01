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
#include "FileInputStream.hpp"


namespace obotcha {

DECLARE_SIMPLE_CLASS(JsonReader) {
public:
    _JsonReader(File f);

    _JsonReader(String content);

    JsonValue get();

private:
    FileInputStream stream;

    String mContent;

    int size;

    JsonValue mValue;

    JsonValue parse();

    JsonValue parse(String);

    
};

}
#endif