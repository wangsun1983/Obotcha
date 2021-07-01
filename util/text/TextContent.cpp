#include "TextContent.hpp"

namespace obotcha {

_TextContent::_TextContent(const Integer &v) {
    mContent = createString(v);
}

_TextContent::_TextContent(const Boolean &v) {
    mContent = createString(v);
}

_TextContent::_TextContent(const Float &v) {
    mContent = createString(v);
}

_TextContent::_TextContent(const Double &v) {
    mContent = createString(v);
}

_TextContent::_TextContent(const Long &v) {
    mContent = createString(v);
}

_TextContent::_TextContent(const Uint8 &v){
    mContent = createString(v);
}

_TextContent::_TextContent(const Uint16 &v){
    mContent = createString(v);
}

_TextContent::_TextContent(const Uint32 &v){
    mContent = createString(v);
}

_TextContent::_TextContent(const Uint64 &v){
    mContent = createString(v);
}

_TextContent::_TextContent(const Byte &v){
    mContent = createString(v);
}

_TextContent::_TextContent(int v){
    mContent = createString(v);
}

_TextContent::_TextContent(bool v){
    mContent = createString(v);
}

_TextContent::_TextContent(float v){
    mContent = createString(v);
}

_TextContent::_TextContent(double v){
    mContent = createString(v);
}

_TextContent::_TextContent(long v){
    mContent = createString(v);
}

_TextContent::_TextContent(char v){
    mContent = createString(v);
}

_TextContent::_TextContent(uint8_t v){
    mContent = createString(v);
}

_TextContent::_TextContent(uint16_t v){
    mContent = createString(v);
}

_TextContent::_TextContent(uint32_t v){
    mContent = createString(v);
}

_TextContent::_TextContent(uint64_t v){
    mContent = createString(v);
}

String _TextContent::get() {
    return mContent;
}

}

