#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpMultiPartParser::_HttpMultiPartParser(const String boundary) {
    //mContentLength = length;
    //mBoundary = createString("--");
    mRawBoundary = boundary;
    mBoundary = st(HttpText)::BoundaryBeginning->append(boundary);
    mBoundaryEnd = mBoundary->append(st(HttpText)::CRLF);
    mPartEnd = mBoundary->append(st(HttpText)::MultiPartEnd);

    BoundaryEnd = mBoundaryEnd->toChars();
    PartEnd = mPartEnd->toChars();

    mStatus = ParseStartBoundry;

    //mEnv = st(Enviroment)::getInstance();

    //CRLF = st(HttpText)::CRLF->toChars();

    mBoundaryIndex = 0;

    mFileStream = nullptr;
    //mMultiPartFile = nullptr;
    endDetector = createCRLFDetector();
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

    if (mMultiPart == nullptr) {
        mMultiPart = createHttpMultiPart(mRawBoundary);
    }

    byte v = 0;
    while (reader->readNext(v) == st(ByteRingArrayReader)::Continue) {
        //printf("HttpMultiPartParser,v is %x,status is %d \n",v,mStatus);
        switch (mStatus) {
            case ParseStartBoundry: {
                if(endDetector->isEnd(v)) {
                    //i got the boundry!!!
                    ByteArray boundary = reader->pop();
                    mStatus = ParseContentInfo;
                    continue;
                }
                break;
            }
            
            case ParseContentInfo: {
                if(endDetector->isEnd(v)) {
                    String info = reader->pop()->toString();
                    if(info->size() == 2 && info->equals(st(HttpText)::CRLF)) {
                        if(mDisposition->getFileName() != nullptr) {
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
                //printf("ParseFormData checkStatus is %d \n",checkStatus);
                int resizeSize = mBoundaryEnd->size();
                switch(checkStatus) {
                    case _PartEnd:
                        resizeSize = mPartEnd->size();
                    case _BoundaryEnd:{
                        ByteArray data = reader->pop();
                        //substring to remove boundary
                        data->quickShrink(data->size() - resizeSize - 2); //the end of data is /r/n,remove it.
                        mMultiPart->addContent(mDisposition->getName(),data->toString());
                        if(checkStatus == _PartEnd) {
                            auto result = mMultiPart;
                            mMultiPart = nullptr;
                            mStatus = ParseStartBoundry;
                            return result;
                        }
                        mStatus = ParseContentInfo;
                    }
                    break;

                    case _None:
                    break;
                }
                break;
            }

            case ParseContent: {
                int checkStatus = checkBoudaryIndex(v);
                //printf("HttpMultiPartParser checkStatus is %d \n",checkStatus);
                int resizeSize = mBoundaryEnd->size(); // multi part end "----xxxx\r\n"
                switch(checkStatus) {
                    case _PartEnd:
                        resizeSize = mPartEnd->size(); //part end "----xxxx--\r\n"
                    case _BoundaryEnd:{
                        ByteArray data = reader->pop();
                        data->quickShrink(data->size() - resizeSize - 2); //the end of data is /r/n,remove it.
                        flushData(data);
                        mFileStream->close();
                        mFileStream = nullptr;
                        mStatus = ParseContentInfo;
                        //printf("HttpMultiPartParser,flush content,checkStatus is %d \n",checkStatus);
                        if(checkStatus == _PartEnd) {
                            auto result = mMultiPart;
                            mMultiPart = nullptr;
                            mDisposition = nullptr;
                            mTransferEncoding = nullptr;
                            mContentType = nullptr;
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
            flushData(data);
        }
    }

    return nullptr;
}

void _HttpMultiPartParser::flushData(ByteArray data) {
    if(mFileStream == nullptr){
        HttpMultiPartFile multiPartFile = createHttpMultiPartFile(mDisposition->getFileName(),mContentType,mDisposition->getName());
        mMultiPart->addFile(multiPartFile);
        mFileStream = createFileOutputStream(multiPartFile->getFile());
        mFileStream->open();
    }
    mFileStream->write(data);
}

// bool _HttpMultiPartParser::isLineEnd(byte &v) {
//     if(v == '\r' && mCRLFIndex == 0) {
//         mCRLFIndex = 1;
//     } else if(v == '\n' && mCRLFIndex == 1) {
//         mCRLFIndex = 0;
//         return true;
//     } else {
//         mCRLFIndex = 0;
//     }

//     return false;
// }

int _HttpMultiPartParser::checkBoudaryIndex(byte &v) {
    if(v == BoundaryEnd[mBoundaryIndex]) {
        if(mBoundaryIndex == (mBoundaryEnd->size() - 1)) {
            mBoundaryIndex = 0;
            return _BoundaryEnd;
        }
        mBoundaryIndex++;
    } else if(v == PartEnd[mBoundaryIndex]) {
        if(mBoundaryIndex == (mPartEnd->size() - 1)) {
            mBoundaryIndex = 0;
            return _PartEnd;
        }
        mBoundaryIndex++;
    } else {
        mBoundaryIndex = 0;
    }

    return _None;
}

} // namespace obotcha