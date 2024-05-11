#include "TextContent.hpp"

namespace obotcha {

#define IMPLE_TEXTCONTENT(X) \
    _TextContent::_TextContent(X &v) { \
        mContent = String::New(v); \
    } \
    _TextContent::_TextContent(const X &v) { \
        mContent = String::New(v); \
    }

IMPLE_TEXTCONTENT(Integer)
IMPLE_TEXTCONTENT(Boolean)
IMPLE_TEXTCONTENT(Float)
IMPLE_TEXTCONTENT(Double)
IMPLE_TEXTCONTENT(Long)
IMPLE_TEXTCONTENT(Uint8)
IMPLE_TEXTCONTENT(Uint16)
IMPLE_TEXTCONTENT(Uint32)
IMPLE_TEXTCONTENT(Uint64)
IMPLE_TEXTCONTENT(Byte)
IMPLE_TEXTCONTENT(String)
IMPLE_TEXTCONTENT(int)
IMPLE_TEXTCONTENT(bool)
IMPLE_TEXTCONTENT(float)
IMPLE_TEXTCONTENT(double)
IMPLE_TEXTCONTENT(long)
IMPLE_TEXTCONTENT(char)
IMPLE_TEXTCONTENT(uint8_t)
IMPLE_TEXTCONTENT(uint16_t)
IMPLE_TEXTCONTENT(uint32_t)
IMPLE_TEXTCONTENT(uint64_t)

#undef IMPLE_TEXTCONTENT

_TextContent::_TextContent(const char * v) {
    mContent = String::New(v);
}

String _TextContent::get() { 
    return mContent;
}

} // namespace obotcha
