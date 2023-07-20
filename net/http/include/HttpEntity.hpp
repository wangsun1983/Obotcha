#ifndef __OBOTCHA_HTTP_ENTITY_HPP__
#define __OBOTCHA_HTTP_ENTITY_HPP__

#include "Object.hpp"
#include "File.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HttpChunk.hpp"

namespace obotcha {

DECLARE_CLASS(HttpEntity) {
public:
    _HttpEntity() = default;
    
    void setMultiPart(HttpMultiPart);
    HttpMultiPart getMultiPart();
    ByteArray getContent();
    void setContent(ByteArray);
    void setChunk(ByteArray);
    void setChunk(File);
    void setChunk(HttpChunk);
    HttpChunk getChunk();

private:
    HttpMultiPart mMultiPart;
    ByteArray mContent;
    HttpChunk mChunk;
};

}
#endif
