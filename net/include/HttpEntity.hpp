#ifndef __OBOTCHA_HTTP_ENTITY_HPP__
#define __OBOTCHA_HTTP_ENTITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "HttpMultiPart.hpp"
#include "HashMap.hpp"
#include "KeyValuePair.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpEntity) {
public:
    _HttpEntity();
    
    void setMultiPart(HttpMultiPart);

    HttpMultiPart getMultiPart();

    ArrayList<KeyValuePair<String,String>> getEncodedKeyValues();

    void setEncodedKeyValues(ArrayList<KeyValuePair<String,String>>);

    ByteArray getContent();
    void setContent(ByteArray);

    String getUpgrade();
    void setUpgrade(String);

private:
    HttpMultiPart mMultiPart;

    ArrayList<KeyValuePair<String,String>>mFormUrlEncodedMap;
    
    ByteArray mContent;

    String mUpgrade;

};

}
#endif
