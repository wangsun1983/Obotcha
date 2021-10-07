#ifndef __OBOTCHA_HTTP_MIME_HPP__
#define __OBOTCHA_HTTP_MIME_HPP__

//according nginx/conf/mime.types
#include <thread>
#include <mutex>

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
        memset(next,0,sizeof(FileTypeSearchNode*) *96);
    }
    
    FileTypeSearchNode* next[96];
    int type;
};

DECLARE_CLASS(HttpMime) {

public:
    _HttpMime();
    void setTypeName(String);
    void setTypeId(int);
    void setSuffix(String);
    
    String getTypeName();
    int getTypeId();
    //String getSuffix();

private:
    static FileTypeSearchNode *mSuffixRootNode;
    static FileTypeSearchNode *mContentTypeNode;

    static void addNode(FileTypeSearchNode *root,const char *,int,int);
    int searchNode(FileTypeSearchNode *root,const char *,int);

    int mType;
};

}
#endif
