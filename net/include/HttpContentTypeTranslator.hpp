#ifndef __OBOTCHA_HTTP_CONTENT_TYPE_TRANSLATOR_HPP__
#define __OBOTCHA_HTTP_CONTENT_TYPE_TRANSLATOR_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "File.hpp"

namespace obotcha {

class FileTypeSearchNode {
public:
    FileTypeSearchNode() {
        type = -1;
    }
    
    FileTypeSearchNode* next[96];
    int type;
};

DECLARE_SIMPLE_CLASS(HttpContentTypeTranslator) {

public:
    static sp<_HttpContentTypeTranslator> getInstance();

    String toType(File);
    String toType(String);
    int suffixToInt(String);
    int typeToInt(String);
    String intToType(int);
    String suffixToType(String);

private:
    _HttpContentTypeTranslator();
    static Mutex mMutex;
    static sp<_HttpContentTypeTranslator> mInstance;
    FileTypeSearchNode *mSuffixRootNode;
    FileTypeSearchNode *mContentTypeNode;

    void addNode(FileTypeSearchNode *root,const char *,int,int);
    int searchNode(FileTypeSearchNode *root,const char *,int);
};

}
#endif
