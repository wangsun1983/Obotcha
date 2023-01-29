#ifndef __OBOTCHA_TEXT_CONTENT_H__
#define __OBOTCHA_TEXT_CONTENT_H__

#include "JsonValue.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _YamlReader;

DECLARE_CLASS(TextContent) {
public:
    enum Type {
        Json = 0,
        Xml,
        Serialize
    };

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
    _TextContent(const String &v);
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
    _TextContent(const char *);

    template <typename T> _TextContent(sp<T> value, int type = Json) {
        switch(type) {
            case Json: {
                JsonValue jvalue = createJsonValue();
                jvalue->importFrom(value);
                mContent = jvalue->toString();
            }
            break;

            case Xml:
                //TODO
            break;

            case Serialize:
                //TODO
            break;
        }
    }

    String get();

private:
    String mContent;
};

} // namespace obotcha

#endif