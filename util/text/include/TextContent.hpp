#ifndef __OBOTCHA_TEXT_CONTENT_H__
#define __OBOTCHA_TEXT_CONTENT_H__

#include "JsonValue.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "OStdInstanceOf.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

namespace obotcha {

class _YamlReader;

DECLARE_CLASS(TextContent) {
public:
    enum Type {
        Json = 0,
        Xml
    };

    _TextContent(Integer &v);
    _TextContent(Boolean &v);
    _TextContent(Float &v);
    _TextContent(Double &v);
    _TextContent(Long &v);
    _TextContent(Uint8 &v);
    _TextContent(Uint16 &v);
    _TextContent(Uint32 &v);
    _TextContent(Uint64 &v);
    _TextContent(Byte &v);
    _TextContent(String &v);
    _TextContent(int &v);
    _TextContent(bool &v);
    _TextContent(float &v);
    _TextContent(double &v);
    _TextContent(long &v);
    _TextContent(char &v);
    _TextContent(uint8_t &);
    _TextContent(uint16_t &);
    _TextContent(uint32_t &);
    _TextContent(uint64_t &);
    _TextContent(const char *);

    template <typename T> _TextContent(sp<T> value, int type = Json) {
        switch(type) {
            case Json: {
                JsonValue jvalue = createJsonValue();
                jvalue->importFrom(value);
                mContent = jvalue->toString();
            }
            break;

            case Xml: {
                XmlDocument doc = createXmlDocument();
                doc->importFrom(value);
                mContent = doc->toString();
            }
            break;
        }
    }

    String get();

private:
    String mContent;
};

} // namespace obotcha

#endif