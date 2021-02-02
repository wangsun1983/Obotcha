#ifndef __OBOTCHA_HTTP_CONTENT_TYPE_TOOL_HPP__
#define __OBOTCHA_HTTP_CONTENT_TYPE_TOOL_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
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

DECLARE_SIMPLE_CLASS(HttpContentTypeTool) {

public:
    static sp<_HttpContentTypeTool> getInstance();

    String toType(File);
    String toType(String);
    int suffixToInt(String);
    int typeToInt(String);
    String intToType(int);
    String suffixToType(String);

private:
    _HttpContentTypeTool();
    static Mutex mMutex;
    static sp<_HttpContentTypeTool> mInstance;
    FileTypeSearchNode *mSuffixRootNode;
    FileTypeSearchNode *mContentTypeNode;

    void addNode(FileTypeSearchNode *root,const char *,int,int);
    int searchNode(FileTypeSearchNode *root,const char *,int);
};

}
#endif
