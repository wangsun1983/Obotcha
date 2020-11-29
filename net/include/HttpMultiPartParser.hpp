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

namespace obotcha {

DECLARE_SIMPLE_CLASS(PartContentDisposition) {
public:
    _PartContentDisposition();
    
    HashMap<String,String> dispositions;
}; 

DECLARE_SIMPLE_CLASS(HttpMultiPartParser) {
public:
    _HttpMultiPartParser(String,int);

    HttpMultiPart parse(ByteRingArrayReader);
    
    String getHeaderBoundary();

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
        ParseContent,
    };

private:

    static const String NewLine;
    static const String TwoNewLine;
    static const String EndLine;
    static const String Boundary;

    const char *mNewLineStr;
    const char *mTwoNewLine;
    const char *mEndLineStr;
    const char *mBoundaryStr;

    int mBoundaryIndex;
    int mBoundaryEndLineIndex;
    int mBoundaryNextLineIndex;
    int mNewLineTextIndex;

    PartContentDisposition parseContentDisposition(String);

    String parseContentType(String);

    HttpMultiPart mMultiPart;

    File mFile;

    FileOutputStream mFileStream;
    
    int mContentLength;

    int mRecvLength;

    String mBoundary;

    int mStatus;

    //ByteRingArrayReader mReader;

    PartContentDisposition mContentDisp;
    
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
