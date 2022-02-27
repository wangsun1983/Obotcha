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

    HttpChunk getChunk();
    //String getUpgradeContent();
    //void setUpgradeContent(String);

    //File getChunkFile();
    //void setChunkFile(File);

    //ArrayList<ByteArray> getChunks();
    //void setChunks(ArrayList<ByteArray>);

private:
    HttpMultiPart mMultiPart;

    //ArrayList<Pair<String,String>>mFormUrlEncodedMap;
    
    ByteArray mContent;

    HttpChunk mChunk;

    //String mUpgrade;

    //File mChunkFile;
    //ArrayList<ByteArray> mChunks;

};

}
#endif
