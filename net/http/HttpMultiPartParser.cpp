#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"

namespace obotcha {

const int _HttpMultiPartParser::Complete = 0;
const int _HttpMultiPartParser::Continue = 1;
const int _HttpMultiPartParser::NotMultiPart = 2;

const int _HttpMultiPartParser::ParseStartBoundry = 0;
const int _HttpMultiPartParser::ParseStartBoundryEnd = 1;
const int _HttpMultiPartParser::ParseContentDisposition = 2;
const int _HttpMultiPartParser::ParseContentDispositionEnd = 3;
const int _HttpMultiPartParser::ParseContentType = 4;
const int _HttpMultiPartParser::ParseContent = 5;

const String _HttpMultiPartParser::NewLine = createString("\r\n");
const String _HttpMultiPartParser::TwoNewLine = createString("\r\n\r\n");
const String _HttpMultiPartParser::EndLine = createString("--");
const String _HttpMultiPartParser::Boundary = createString("boundary");

//----------------------- PartContentDisposition --------------------
_PartContentDisposition::_PartContentDisposition() {
    dispositions = createHashMap<String,String>();
}

_HttpMultiPartParser::_HttpMultiPartParser(String contenttype,int length) {
    mMultiPart = createHttpMultiPart();
    mContentLength = length;

    //start parse boundary
    ArrayList<String> strings = contenttype->split(";");
    printf("contenttype is %s size is %d \n",contenttype->toChars(),strings->size());
    ListIterator<String> iterator = strings->getIterator();

    while(iterator->hasValue()) {
        String v = iterator->getValue();
        printf("_HttpMultiPartParser v is %s \n",v->toChars());
        if(v->indexOfIgnoreCase(Boundary) == -1) {
            iterator->next();
            continue;
        }

        ArrayList<String> sp = v->split("=");
        if(sp->size() == 2) {
            mBoundary = sp->get(1);
            String start = createString("--");
            mBoundary = start->append(mBoundary);

            printf("_HttpMultiPartParser mBoundary is %s \n",mBoundary->toChars());
            mBoundaryStr = mBoundary->toChars();
            break;
        }
        
        iterator->next();
    }

    mStatus = ParseStartBoundry;

    mEnv = st(Enviroment)::getInstance();

    mNewLineStr = NewLine->toChars();
    mEndLineStr = EndLine->toChars();
    mTwoNewLine = TwoNewLine->toChars();

    mBoundaryIndex = 0;
    mBoundaryEndLineIndex = 0;
    mBoundaryNextLineIndex = 0;
    mNewLineTextIndex = 0;

    mBoundaryBuff = nullptr;
    mBoundaryEndingBuff = nullptr;
    mContentDispositionBuff = nullptr;
    mContentTypeBuff = nullptr;
    mContentBuff = nullptr;
}

//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA =>--boundary
//Content-Disposition: form-data;name="text"
//
//title
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA
//Content-Disposition: form-data;name="file";filename="chrome.png"
//Content-Type: image/png
//PNG ..... content of chrome.png .....
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA--
HttpMultiPart _HttpMultiPartParser::parse(ByteRingArrayReader reader) {
    printf("parse mBoundary is %s,status is %d \n",mBoundary->toChars(),mStatus);
    if(mBoundary == nullptr) {
        return nullptr;
    }
    printf("HttpMultiPartParser parse trace1 \n");

    byte v = 0;

    while(reader->readNext(v) == ByteRingArrayReadContinue) {
        //printf("HttpMultiPartParser parse trace2 \n");

        switch(mStatus) {
            case ParseStartBoundry:{
                //printf("ParseStartBoundry v is %x,mBoundaryStr[mBoundaryIndex] is %x \n",v,mBoundaryStr[mBoundaryIndex]);
                if(v == mBoundaryStr[mBoundaryIndex]) {
                    if(mBoundaryIndex == (mBoundary->size()-1)) {
                        mBoundaryIndex = 0;
                        reader->pop();
                        mStatus = ParseStartBoundryEnd;
                    }
                    mBoundaryIndex++;
                } else {
                    mBoundaryIndex = 0;
                }
                continue;
            }
            break;

            case ParseStartBoundryEnd:{
                //printf("ParseStartBoundryEnd v is %x \n",v);
                if(v == mNewLineStr[mBoundaryEndLineIndex]) {
                    if(mBoundaryEndLineIndex == (NewLine->size()-1)) {
                        mBoundaryEndLineIndex = 0;
                        reader->pop();
                        mStatus = ParseContentDisposition;
                    }
                    mBoundaryEndLineIndex++;
                } else if(v == mEndLineStr[mBoundaryEndLineIndex]){
                    mBoundaryEndLineIndex = 0;
                    reader->pop();
                    return mMultiPart;
                } else {
                    mBoundaryEndLineIndex = 0;
                }
            }
            break;

            case ParseContentDisposition: {
                //printf("ParseContentDisposition v is %c \n",v);
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == (NewLine->size()-1)) {
                        mNewLineTextIndex = 0;
                        
                        if(mContentDispositionBuff == nullptr) {
                            mContentDispositionBuff = reader->pop();
                        } else {
                            mContentDispositionBuff->append(reader->pop());
                        }
                        printf("mContentDispositionBuff v is %s \n",mContentDispositionBuff->toString()->toChars());
                        mContentDisp = parseContentDisposition(mContentDispositionBuff->toString());

                        mContentDispositionBuff = nullptr;
                        mContentType = nullptr;
                        if(mContentDisp->dispositions->get("filename") != nullptr) {
                            mStatus = ParseContentType;
                        } else {
                            mStatus = ParseContentDispositionEnd;
                        }

                        continue;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContentDispositionEnd: {
                //printf("ParseContentDispositionEnd v is %x \n",v);
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == (NewLine->size()-1)) {
                        mNewLineTextIndex = 0;
                        reader->pop();
                        mStatus = ParseContent;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContentType:{
                //printf("ParseContentType v is %x \n",v);
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == 1) {
                        mNewLineTextIndex = 0;
                        if(mContentTypeBuff == nullptr) {
                            mContentTypeBuff = reader->pop();
                        } else {
                            mContentTypeBuff->append(reader->pop());
                        }

                        mContentType = parseContentType(mContentTypeBuff->toString());
                        mStatus = ParseContentDispositionEnd;
                        continue;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContent:
                //printf("ParseContent v is %c \n",v);
                if(v == mBoundaryStr[mBoundaryIndex]) {
                    if(mBoundaryIndex == (mBoundary->size()-1)) {
                        //flush data
                        mBoundaryIndex = 0;
                        ByteArray content = reader->pop();
                        //content->qucikShrink(content->size() - mBoundary->size());

                        if(mContentType == nullptr) {
                            if(mContentBuff != nullptr) {
                                mContentBuff->append(content);
                            } else {
                                mContentBuff = content;
                            }

                            String value = mContentBuff->toString();
                            //printf("ParseContent value is %s \n",value->toChars());
                            value = value->subString(0,content->size() - mBoundary->size()- NewLine->size());
                            String name = mContentDisp->dispositions->get(st(HttpMultiPartBlock)::TagName);
                            HttpMultiPartBlock block = createHttpMultiPartBlock(name,value);
                            mMultiPart->addPartData(block);

                            mContentDisp = nullptr;
                            mContentBuff = nullptr;
                        } else {
                            //hit complete flush file
                            if(mFileStream == nullptr) {
                                printf("ParseContent createFile");
                                String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                                String filename = mContentDisp->dispositions->get("filename");
                                mFile = createFile(filepath->append(filename));
                                mFile->createNewFile();
                                mFileStream = createFileOutputStream(mFile);
                                mFileStream->open();
                            } 
                            
                            if(mContentBuff == nullptr) {
                                mContentBuff = content;
                            } else {
                                mContentBuff->append(content);
                            }
                            
                            printf("mContentBuff size is %d \n",mContentBuff->size());
                            mContentBuff->qucikShrink(mContentBuff->size() - mBoundary->size() - NewLine->size());
                            printf("mContentBuff2 size is %d \n",mContentBuff->size());
                            mFileStream->write(mContentBuff);
                            mFileStream->flush();
                            mFileStream->close();
                            mFileStream = nullptr;
                            mContentBuff = nullptr;
                            mContentType = nullptr;

                            HttpMultiPartFile file = createHttpMultiPartFile(mFile);
                            mMultiPart->addPartData(file);
                        }
                        mStatus = ParseStartBoundryEnd;
                        continue;
                    }
                    mBoundaryIndex++;
                } else {
                    mBoundaryIndex = 0;
                }
                break;
        }
    }
    
    printf("parse trace3 \n");
    //check whether there is no analyze buff
    if(reader->getReadableLength() != 0) {
        switch(mStatus) {
            case ParseStartBoundry:{
                reader->pop();
            }
            break;

            case ParseStartBoundryEnd:{
                reader->pop();
            }
            break;

            case ParseContentDisposition:{
                if(mContentDispositionBuff == nullptr) {
                    mContentDispositionBuff = reader->pop();
                } else {
                    mContentDispositionBuff->append(reader->pop());
                }
            }
            break;

            case ParseContentDispositionEnd:{
                reader->pop();
            }
            break;

            case ParseContentType:{
                if(mContentTypeBuff == nullptr) {
                    mContentTypeBuff = reader->pop();
                } else {
                    mContentTypeBuff->append(reader->pop());
                }
            }
            break;

            case ParseContent:{
                if(mContentType != nullptr) {
                    printf("parse trace4 \n");
                    if(mFileStream == nullptr) {
                        String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                        String filename = mContentDisp->dispositions->get("filename");
                        mFileStream = createFileOutputStream(filepath->append(filename));
                        mFileStream->open();
                    }

                    ByteArray content = reader->pop();
                    
                    content->qucikShrink(content->size() - mBoundaryIndex);
                    if(mContentBuff != nullptr) {
                        mContentBuff->append(content);
                    } else {
                        mContentBuff = content;
                    }

                    printf("write size is %d \n",content->size());

                    mFileStream->write(mContentBuff);
                    mFileStream->flush();
                    mContentBuff = nullptr;
                } else {
                    if(mContentBuff != nullptr) {
                        mContentBuff->append(reader->pop());
                    } else {
                        mContentBuff = reader->pop();
                    }
                }
            }
            break;
        }
    }

    return nullptr;
}

String _HttpMultiPartParser::parseContentType(String content) {
    ArrayList<String> split = content->split(":");
    if(split->size() != 2) {
        return nullptr;
    }

    String type = split->get(1);

    return type->trimAll();
}

//Content-Disposition: form-data;name="file";filename="chrome.png"
PartContentDisposition _HttpMultiPartParser::parseContentDisposition(String position) {
    PartContentDisposition data = createPartContentDisposition();
    printf("parseContentDisposition position is %s \n",position->toChars());
    ArrayList<String> split1 = position->split(";");
    ListIterator<String> iterator1 = split1->getIterator();
    while(iterator1->hasValue()) {
        String tag = iterator1->getValue();
        ArrayList<String> split2 = tag->split(":");
        if(split2 == nullptr ) {
            split2 = tag->split("=");
        }

        if(split2 != nullptr) {
            String tag = split2->get(0)->trimAll();
            String value = split2->get(1)->trimAll();
            if(value->charAt(0) == '"') {
                //value = value->subString(1,value->size()-1);

                //find last '""
                int next = value->size() - 1;
                while(next != 0) {
                    if(value->charAt(next) == '"') {
                        break;
                    }

                    next--;
                }

                value = value->subString(1,next - 1);
            }
            
            data->dispositions->put(tag,value);
        }

        iterator1->next();
    }

    //wangsl
    //MapIterator<String,String> dumpite = data->dispositions->getIterator();
    //while(dumpite->hasValue()) {
    //    printf("key is %s , value is %s \n",dumpite->getKey()->toChars(),dumpite->getValue()->toChars());
    //    dumpite->next();
    //}
    //wangsl

    return data;
}

}