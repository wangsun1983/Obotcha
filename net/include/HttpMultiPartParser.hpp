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
#include "CRLFDetector.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartParser) {
public:
    _HttpMultiPartParser(const String);

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

    //const char *CRLF;
    const char *PartEnd;
    const char *BoundaryEnd;

    HttpMultiPart mMultiPart;

    FileOutputStream mFileStream;

    String mBoundary;
    String mBoundaryEnd;
    String mPartEnd;
    String mRawBoundary;

    int mStatus;

    int mBoundaryIndex;

    HttpHeaderContentDisposition mDisposition;
    HttpHeaderTransferEncoding mTransferEncoding;
    HttpHeaderContentType mContentType;
    
    //bool isLineEnd(byte &v);
    CRLFDetector endDetector;
    int checkBoudaryIndex(byte &v);
    void flushData(ByteArray);

    ByteArray mCacheContent;
};

}
#endif
