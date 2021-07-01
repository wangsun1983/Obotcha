#ifndef __OBOTCHA_TEXT_CONTENT_H__
#define __OBOTCHA_TEXT_CONTENT_H__

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "JsonValue.hpp"

namespace obotcha {

class _YamlReader;

DECLARE_SIMPLE_CLASS(TextContent) {

public:
    _TextContent(const Integer &v);
    _TextContent(const Boolean &v);
    _TextContent(const Float &v);
    _TextContent(const Double &v);
    _TextContent(const Long &v);
    _TextContent(const Uint8 &v);
    _TextContent(const Uint16 &v);
    _TextContent(const Uint32 &v);
    _TextContent(const Uint64 &v);
    _TextContent(const Byte &v);
    _TextContent(int v);
    _TextContent(bool v);
    _TextContent(float v);
    _TextContent(double v);
    _TextContent(long v);
    _TextContent(char v);
    _TextContent(uint8_t);
    _TextContent(uint16_t);
    _TextContent(uint32_t);
    _TextContent(uint64_t);

    template<typename T> 
    _TextContent(sp<T> value) {
        JsonValue jvalue = createJsonValue();
        jvalue->importFrom(value);
        mContent = jvalue->toString();
    }

    String get();

private:
    String mContent;
};

}

#endif