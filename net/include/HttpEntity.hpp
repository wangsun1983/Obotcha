#ifndef __OBOTCHA_HTTP_ENTITY_HPP__
#define __OBOTCHA_HTTP_ENTITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HashMap.hpp"
#include "Pair.hpp"
#include "File.hpp"
#include "HttpChunk.hpp"

namespace obotcha {

DECLARE_CLASS(HttpEntity) {
public:
    _HttpEntity();
    
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
