#ifndef __OBOTCHA_HTTP_MULTI_PART_PARSER_HPP__
#define __OBOTCHA_HTTP_MULTI_PART_PARSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpMultiPart.hpp"
#include "ByteRingArrayReader.hpp"
#include "FileOutputStream.hpp"
#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderContentDisposition.hpp"
#include "HttpHeaderContentType.hpp"
#include "CRLFDetector.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartParser) {
public:
    explicit _HttpMultiPartParser(const String);

    HttpMultiPart parse(ByteRingArrayReader);
    
private:
     enum BoundaryCheckStatus {
        PartEnd = 0,
        BoundaryEnd,
        None,
    };

    enum class Status {
        ParseStartBoundry = 0,
        ParseContentInfo,
        ParseFormData,
        ParseContent,
    };

    const char *mPartEndStr;
    const char *mBoundaryEndStr;

    HttpMultiPart mMultiPart;

    FileOutputStream mFileStream = nullptr;

    String mBoundary;
    String mBoundaryEnd;
    String mPartEnd;
    String mRawBoundary;

    Status mStatus = Status::ParseStartBoundry;
    size_t mBoundaryEndLength;
    size_t mPartEndLength;

    size_t mBoundaryIndex = 0;

    HttpHeaderContentDisposition mDisposition;
    HttpHeaderTransferEncoding mTransferEncoding;
    HttpHeaderContentType mContentType;

    CRLFDetector endDetector = createCRLFDetector();
    int getParseContentStatus(byte &v);
    void saveContent(ByteArray);

    ByteArray mCacheContent;
};

}
#endif
