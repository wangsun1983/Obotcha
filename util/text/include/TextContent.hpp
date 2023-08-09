#ifndef __OBOTCHA_TEXT_CONTENT_H__
#define __OBOTCHA_TEXT_CONTENT_H__

#include "JsonValue.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "OStdInstanceOf.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"
#include "InitializeException.hpp"

namespace obotcha {

class _YamlReader;

DECLARE_CLASS(TextContent) {
public:
    enum class Format {
        Json = 0,
        Xml
    };

#define DECLARE_TEXTCONTENT(X) \
    explicit _TextContent(X &v);\
    explicit _TextContent(const X &v);

    DECLARE_TEXTCONTENT(Integer);
    DECLARE_TEXTCONTENT(Boolean);
    DECLARE_TEXTCONTENT(Float);
    DECLARE_TEXTCONTENT(Double);
    DECLARE_TEXTCONTENT(Long);
    DECLARE_TEXTCONTENT(Uint8);
    DECLARE_TEXTCONTENT(Uint16);
    DECLARE_TEXTCONTENT(Uint32);
    DECLARE_TEXTCONTENT(Uint64);
    DECLARE_TEXTCONTENT(Byte);
    DECLARE_TEXTCONTENT(String);
    DECLARE_TEXTCONTENT(int);
    DECLARE_TEXTCONTENT(bool);
    DECLARE_TEXTCONTENT(float);
    DECLARE_TEXTCONTENT(double);
    DECLARE_TEXTCONTENT(long);
    DECLARE_TEXTCONTENT(char);
    DECLARE_TEXTCONTENT(uint8_t);
    DECLARE_TEXTCONTENT(uint16_t);
    DECLARE_TEXTCONTENT(uint32_t);
    DECLARE_TEXTCONTENT(uint64_t);

#undef DECLARE_TEXTCONTENT

    explicit _TextContent(const char *);

    template <typename T> _TextContent(sp<T> value, 
                                      _TextContent::Format type = _TextContent::Format::Json) {
        switch(type) {
            case _TextContent::Format::Json: {
                JsonValue jvalue = createJsonValue();
                jvalue->importFrom(value);
                mContent = jvalue->toString();
            }
            break;

            case _TextContent::Format::Xml: {
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