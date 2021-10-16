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
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(HttpEntity) {
public:
    _HttpEntity();
    
    void setMultiPart(HttpMultiPart);
    HttpMultiPart getMultiPart();

    ByteArray getContent();
    void setContent(ByteArray);

    String getUpgrade();
    void setUpgrade(String);

    File getChunkFile();
    void setChunkFile(File);

private:
    HttpMultiPart mMultiPart;

    ArrayList<KeyValuePair<String,String>>mFormUrlEncodedMap;
    
    ByteArray mContent;

    String mUpgrade;

    File mChunkFile;

};

}
#endif
