#include "HttpMultiPartParser.hpp"
#include "HttpHeader.hpp"
#include "Enviroment.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

_HttpMultiPartParser::_HttpMultiPartParser(const String boundary):mRawBoundary(boundary) {
    mBoundary = st(HttpText)::BoundaryBeginning->append(boundary);
    mBoundaryEnd = mBoundary->append(st(HttpText)::CRLF);
    mPartEnd = mBoundary->append(st(HttpText)::MultiPartEnd);
    mBoundaryEndStr = mBoundaryEnd->toChars();
    mPartEndStr = mPartEnd->toChars();
    mBoundaryEndLength = mBoundaryEnd->size();
    mPartEndLength = mPartEnd->size();
}

/**
* RFC1867 6. Examples
* The client might send back the following data:
*    Content-type: multipart/form-data, boundary=AaB03x
*
*    --AaB03x
*    content-disposition: form-data; name="field1"
*
*    Joe Blow
*    --AaB03x
*    content-disposition: form-data; name="pics"; filename="file1.txt"
*    Content-Type: text/plain
*
*        ... contents of file1.txt ...
*    --AaB03x--
*/
HttpMultiPart _HttpMultiPartParser::parse(ByteRingArrayReader reader) {
    byte v = 0;
    while (reader->readNext(v) == st(Defination)::ContinueRead) {
        switch (mStatus) {
            case _HttpMultiPartParser::Status::ParseStartBoundry: {
                if(endDetector->isEnd(v)) {
                    //got the boundry!!!,drop it
                    reader->pop();
                    mMultiPart = createHttpMultiPart(mRawBoundary);
                    mStatus = _HttpMultiPartParser::Status::ParseContentInfo;
                    continue;
                }
                break;
            }
            
            case _HttpMultiPartParser::Status::ParseContentInfo: {
                if(endDetector->isEnd(v)) {
                    String info = reader->pop()->toString();
                    if(info->size() == 2 && info->equals(st(HttpText)::CRLF)) {
                        mStatus = (mDisposition->getFileName() == nullptr)?_HttpMultiPartParser::Status::ParseFormData
                                                                          :_HttpMultiPartParser::Status::ParseContent;
                        continue;
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

            case _HttpMultiPartParser::Status::ParseFormData:
            case _HttpMultiPartParser::Status::ParseContent: {
                int checkStatus = getParseContentStatus(v);
                int resizeSize = mBoundaryEnd->size(); // multi part end "----xxxx\r\n"
                switch(checkStatus) {
                    case PartEnd:
                        resizeSize = mPartEnd->size(); //part end "----xxxx--\r\n"
                        [[fallthrough]];
                    case BoundaryEnd:{
                        ByteArray data = reader->pop();
                        if(mCacheContent != nullptr) {
                            mCacheContent->append(data);
                            data = mCacheContent;
                            mCacheContent = nullptr;
                        }
                        
                        data->quickShrink(data->size() - resizeSize - 2); //the end of data is /r/n,remove it.
                        if(mStatus == _HttpMultiPartParser::Status::ParseFormData) {
                            mMultiPart->addContent(mDisposition->getName(),data->toString());
                        } else {
                            saveContent(data);
                            mFileStream->close();
                            mFileStream = nullptr;    
                        }

                        mStatus = _HttpMultiPartParser::Status::ParseContentInfo;
                        if(checkStatus == PartEnd) {
                            mDisposition = nullptr;
                            return mMultiPart;
                        }
                    }
                    [[fallthrough]];
                    case None:
                    break;
                }
                break;
            }
        }
    }
    
    if(mStatus == _HttpMultiPartParser::Status::ParseContent) {
        ByteArray data = reader->pop();
        Inspect(data == nullptr || data->size() == 0,nullptr)

        if(mBoundaryIndex == 0) {
            saveContent(data);
        } else {
            st(ByteArray)::Combine(mCacheContent,data);
            // if(mCacheContent == nullptr) {
            //     mCacheContent = data;
            // } else {
            //     mCacheContent->append(data);
            // }
        }
    }
    return nullptr;
}

void _HttpMultiPartParser::saveContent(ByteArray data) {
    if(mFileStream == nullptr){
        HttpMultiPartFile multiPartFile = createHttpMultiPartFile(mDisposition->getFileName(),
                                                                  mContentType,
                                                                  mDisposition->getName());
        mMultiPart->addFile(multiPartFile);
        mFileStream = createFileOutputStream(multiPartFile->getFile());
        mFileStream->open();
    }
    mFileStream->write(data);
}

int _HttpMultiPartParser::getParseContentStatus(byte &v) {
    if(mBoundaryIndex < mBoundaryEndLength && v == mBoundaryEndStr[mBoundaryIndex]) {
        if(mBoundaryIndex == (mBoundaryEndLength - 1)) {
            mBoundaryIndex = 0;
            return BoundaryEnd;
        }
        mBoundaryIndex++;
    } else if(mBoundaryIndex < mPartEndLength && v == mPartEndStr[mBoundaryIndex]) {
        if(mBoundaryIndex == (mPartEndLength - 1)) {
            mBoundaryIndex = 0;
            return PartEnd;
        }
        mBoundaryIndex++;
    } else {
        mBoundaryIndex = 0;
    }

    return None;
}

} // namespace obotcha