#ifndef __OBOTCHA_HTTP_ENTITY_HPP__
#define __OBOTCHA_HTTP_ENTITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpEntity) {
public:
    _HttpEntity();
    
    void setMultiPart(HttpMultiPart);

    HttpMultiPart getMultiPart();

    HashMap<String,String> getEncodedKeyValues();

    void setEncodedKeyValues(HashMap<String,String>);

    ByteArray getContent();
    
    void setContent(ByteArray);

private:
    HttpMultiPart mMultiPart;

    HashMap<String,String>mFormUrlEncodedMap;
    
    ByteArray mContent;

};

}
#endif
