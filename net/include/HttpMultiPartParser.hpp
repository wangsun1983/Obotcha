#ifndef __OBOTCHA_HTTP_MULTI_PART_PARSER_HPP__
#define __OBOTCHA_HTTP_MULTI_PART_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Pipe.hpp"
#include "Mutex.hpp"
#include "HttpMultiPart.hpp"
#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "FileOutputStream.hpp"
#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderContentType.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartParser) {
public:
    _HttpMultiPartParser(const String,int);

    HttpMultiPart parse(ByteRingArrayReader);
    
    //String getHeaderBoundary();
private:

     enum BoundaryCheckStatus {
        _PartEnd = 0,
        _BoundaryEnd,
        _None,
    };

    enum ParseStatus {
        ParseStartBoundry = 0,
        ParseContentInfo,
        ParseFormData,
        ParseContent,
    };

    const char *CRLF;
    const char *PartEnd;
    const char *BoundaryEnd;

    HttpMultiPart mMultiPart;

    //File mFile;
    HttpMultiPartFile mMultiPartFile;

    FileOutputStream mFileStream;
    
    int mContentLength;

    int mRecvLength;

    String mBoundary;
    String mBoundaryEnd;
    String mPartEnd;

    int mStatus;

    //ByteRingArrayReader mReader;

    HashMap<String,String> mContentDisp;
    Enviroment mEnv;

    int mCRLFIndex;
    int mBoundaryIndex;

    HttpHeaderContentDisposition mDisposition;
    HttpHeaderTransferEncoding mTransferEncoding;
    HttpHeaderContentType mContentType;
    
    bool isLineEnd(byte &v);
    int checkBoudaryIndex(byte &v);
    void flushData(ByteArray,int);
};

}
#endif
