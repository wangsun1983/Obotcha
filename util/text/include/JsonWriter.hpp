#ifndef __OBOTCHA_JSON_WRITE_H__
#define __OBOTCHA_JSON_WRITE_H__

#include "Object.hpp"
#include "String.hpp"
#include "JsonValue.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

DECLARE_CLASS(JsonWriter) {
public:
    explicit _JsonWriter(File f);
    explicit _JsonWriter(String path);
    explicit _JsonWriter(const char *);

    void write(JsonValue value);

    void close();

private:
    FileOutputStream stream;
};

} // namespace obotcha
#endif