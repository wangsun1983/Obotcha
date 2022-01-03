#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpMultiPartParser::_HttpMultiPartParser(const String boundary,
                                           int length) {
    mContentLength = length;
    mBoundary = createString("--");
    mBoundary = mBoundary->append(boundary);

    mBoundaryEnd = mBoundary->append("\r\n");
    mPartEnd = mBoundary->append("--\r\n");

    BoundaryEnd = mBoundaryEnd->toChars();
    PartEnd = mPartEnd->toChars();

    mStatus = ParseStartBoundry;

    mEnv = st(Enviroment)::getInstance();

    CRLF = st(HttpText)::CRLF->toChars();

    mBoundaryIndex = 0;

    mFileStream = nullptr;
    mMultiPartFile = nullptr;
}

// String _HttpMultiPartParser::getHeaderBoundary() {
//    return mBoundaryHeader;
//}

//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA =>--boundary
// Content-Disposition: form-data;name="text"
//
// title
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA
// Content-Disposition: form-data;name="file";filename="chrome1.png"
// Content-Type: image/png
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA
// Content-Disposition: form-data;name="file";filename="chrome2.png"
// Content-Type: image/png
//.......
// PNG ..... content of chrome.png .....
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA--
HttpMultiPart _HttpMultiPartParser::parse(ByteRingArrayReader reader) {
    if (mBoundary == nullptr) {
        return nullptr;
    }

    if (mMultiPart == nullptr) {
        mMultiPart = createHttpMultiPart();
    }

    byte v = 0;
    while (reader->readNext(v) == st(ByteRingArrayReader)::Continue) {
        switch (mStatus) {
            case ParseStartBoundry: {
                if(isLineEnd(v)) {
                    //i got the boundry!!!
                    ByteArray boundary = reader->pop();
                    mStatus = ParseContentInfo;
                    continue;
                }
                break;
            }
            
            case ParseContentInfo: {
                if(isLineEnd(v)) {
                    String info = reader->pop()->toString();
                    if(info->size() == 2 && info->equals(st(HttpText)::CRLF)) {
                        if(mDisposition->filename != nullptr) {
                            mStatus = ParseContent;
                        } else {
                            mStatus = ParseFormData;
                        }
                        break;
                    }

                    auto params = info->split(":");
                    String head = params->get(0);
                    String data = params->get(1);
                    
                    int type = st(HttpHeader)::findId(head);
                    switch(type) {
                        case st(HttpHeader)::TypeContentDisposition:
                            mDisposition = createHttpHeaderContentDisposition(data);
                        break;

                        case st(HttpHeader)::TypeContentType:
                            mContentType = createHttpHeaderContentType(data);
                        break;

                        case st(HttpHeader)::TypeTransferEncoding:
                            mTransferEncoding = createHttpHeaderTransferEncoding(data);
                        break;
                    }
                }
                break;
            }

            case ParseFormData:{
                int checkStatus = checkBoudaryIndex(v);
                switch(checkStatus) {
                    case _PartEnd:
                    case _BoundaryEnd:{
                        ByteArray data = reader->pop();
                        mMultiPart->contents->add(createKeyValuePair<String,String>(mDisposition->name,data->toString()));
                        mStatus = ParseContentInfo;
                        if(checkStatus == _PartEnd) {
                            auto result = mMultiPart;
                            mMultiPart = nullptr;
                            return result;
                        }
                    }
                    break;

                    case _None:
                    break;
                }
                break;
            }

            case ParseContent: {
                int checkStatus = checkBoudaryIndex(v);
                int resizeSize = mBoundaryEnd->size(); // multi part end "----xxxx\r\n"
                switch(checkStatus) {
                    case _PartEnd:
                        resizeSize = mPartEnd->size(); //part end "----xxxx--\r\n"
                    case _BoundaryEnd:{
                        ByteArray data = reader->pop();
                        flushData(data,resizeSize + 2); //last data has "\r\n"
                        mFileStream->close();
                        mFileStream = nullptr;
                        mStatus = ParseContentInfo;
                        if(checkStatus == _PartEnd) {
                            auto result = mMultiPart;
                            mMultiPart = nullptr;
                            return result;
                        }
                    }

                    case _None:
                    break;
                }
                break;
            }
        }
    }

    if(mStatus == ParseContent && mBoundaryIndex == 0) {
        ByteArray data = reader->pop();
        if(data != nullptr && data->size() != 0) {
            flushData(data,0);
        }
    }

    return nullptr;
}

void _HttpMultiPartParser::flushData(ByteArray data,int resizeSize) {
    if(mFileStream == nullptr){
        HttpMultiPartFile multiPartFile = createHttpMultiPartFile(mDisposition->filename);
        mMultiPart->files->add(multiPartFile);
        mFileStream = createFileOutputStream(multiPartFile->getFile());
        mFileStream->open();
    }
    data->quickShrink(data->size() - resizeSize);
    mFileStream->write(data);
}

bool _HttpMultiPartParser::isLineEnd(byte &v) {
    if(v == '\r' && mCRLFIndex == 0) {
        mCRLFIndex = 1;
    } else if(v == '\n' && mCRLFIndex == 1) {
        mCRLFIndex = 0;
        return true;
    } else {
        mCRLFIndex = 0;
    }

    return false;
}

int _HttpMultiPartParser::checkBoudaryIndex(byte &v) {
    if(v == PartEnd[mBoundaryIndex]){
        if(mBoundaryIndex == (mPartEnd->size() - 1)){
            mBoundaryIndex = 0;
            return _PartEnd;
        }
        mBoundaryIndex++;
    } else if(v == BoundaryEnd[mBoundaryIndex]) {
        if(mBoundaryIndex == (mBoundaryEnd->size() -1)){
            mBoundaryIndex = 0;
            return _BoundaryEnd;
        }
        mBoundaryIndex++;
    }  else {
        mBoundaryIndex = 0;
    }

    return _None;
}


} // namespace obotcha