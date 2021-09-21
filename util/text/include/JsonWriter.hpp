#ifndef __OBOTCHA_JSON_WRITE_H__
#define __OBOTCHA_JSON_WRITE_H__

#include "Boolean.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"

#include "JsonValue.hpp"

#include "File.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

DECLARE_CLASS(JsonWriter) {
public:
    _JsonWriter(File f);
    _JsonWriter(String path);
    _JsonWriter(const char *);

    void write(JsonValue value);

    void close();

private:
    FileOutputStream stream;
};

} // namespace obotcha
#endif