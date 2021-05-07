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
#include "HttpFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMultiPartParser) {
public:
    _HttpMultiPartParser(const String&,int);

    HttpMultiPart parse(ByteRingArrayReader);
    
    //String getHeaderBoundary();

    enum Status {
        Complete = 0,
        Continue,
        NotMultiPart,
    };

    enum ParseStatus {
        ParseStartBoundry = 0,
        ParseStartBoundryEnd,
        ParseContentDisposition,
        ParseContentDispositionEnd,
        ParseContentType,
        ParseContentSkipNewLine,
        ParseContent,
    };

private:

    const char *CRLF;
    const char *MultiPartEnd;
    const char *Boundary;

    int mBoundaryIndex;
    int mBoundaryEndLineIndex;
    int mBoundaryNextLineIndex;
    int mNewLineTextIndex;

    HashMap<String,String> parseContentDisposition(String);

    String parseContentType(String);

    HttpMultiPart mMultiPart;

    //File mFile;
    HttpFile mHttpFile;

    FileOutputStream mFileStream;
    
    int mContentLength;

    int mRecvLength;

    String mBoundary;

    int mStatus;

    //ByteRingArrayReader mReader;

    HashMap<String,String> mContentDisp;
    
    String mBoundaryHeader;

    String mContentType;

    ByteArray mBoundaryBuff;

    ByteArray mBoundaryEndingBuff;

    ByteArray mContentDispositionBuff;

    ByteArray mContentTypeBuff;

    ByteArray mContentBuff;

    Enviroment mEnv;
};

}
#endif
