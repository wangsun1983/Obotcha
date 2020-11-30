#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"

namespace obotcha {

const String _HttpMultiPartParser::NewLine = createString("\r\n");
const String _HttpMultiPartParser::TwoNewLine = createString("\r\n\r\n");
const String _HttpMultiPartParser::EndLine = createString("--\r\n");
const String _HttpMultiPartParser::Boundary = createString("boundary");
const String _HttpMultiPartParser::MultiPartNameTag = createString("name");

//----------------------- PartContentDisposition --------------------
_PartContentDisposition::_PartContentDisposition() {
    dispositions = createHashMap<String,String>();
}

_HttpMultiPartParser::_HttpMultiPartParser(String contenttype,int length) {
    mContentLength = length;
    mBoundaryHeader = contenttype;
    printf("create content is %s \n",mBoundaryHeader->toChars());
    //start parse boundary
    ArrayList<String> strings = contenttype->split(";");
    ListIterator<String> iterator = strings->getIterator();

    while(iterator->hasValue()) {
        String v = iterator->getValue();
        if(v->indexOfIgnoreCase(Boundary) == -1) {
            iterator->next();
            continue;
        }

        ArrayList<String> sp = v->split("=");
        if(sp->size() == 2) {
            mBoundary = sp->get(1);
            String start = createString("--");
            mBoundary = start->append(mBoundary);

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

String _HttpMultiPartParser::getHeaderBoundary() {
    return mBoundaryHeader;
}

//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA =>--boundary
//Content-Disposition: form-data;name="text"
//
//title
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA
//Content-Disposition: form-data;name="file";filename="chrome1.png"
//Content-Type: image/png
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA
//Content-Disposition: form-data;name="file";filename="chrome2.png"
//Content-Type: image/png
//.......
//PNG ..... content of chrome.png .....
//--------WebKitFormBoundaryrGKCBY7qhFd3TrwA--
HttpMultiPart _HttpMultiPartParser::parse(ByteRingArrayReader reader) {
    if(mBoundary == nullptr) {
        return nullptr;
    }
    
    byte v = 0;
    HttpMultiPart part = createHttpMultiPart();

    while(reader->readNext(v) == ByteRingArrayReadContinue) {
        switch(mStatus) {
            case ParseStartBoundry:{
                printf("ParseStartBoundry start Boundary start,mBoundaryIndex is %d v is %c\n",mBoundaryIndex,v);
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
                printf("ParseStartBoundry start ParseStartBoundryEnd start,mBoundaryEndLineIndex is %d \n",mBoundaryEndLineIndex);
                if(v == mNewLineStr[mBoundaryEndLineIndex]) {
                    if(mBoundaryEndLineIndex == (NewLine->size()-1)) {
                        mBoundaryEndLineIndex = 0;
                        reader->pop();
                        printf("ParseStartBoundry start ParseStartBoundryEnd ParseContentDisposition \n");
                        mStatus = ParseContentDisposition;
                        continue;
                    }
                    mBoundaryEndLineIndex++;
                } else if(v == mEndLineStr[mBoundaryEndLineIndex]){
                    printf("ParseStartBoundry start ParseStartBoundryEnd trace3,mBoundaryEndLineIndex is %d,v is %c \n",mBoundaryEndLineIndex,v);
                    if(mBoundaryEndLineIndex == (EndLine->size()-1)) {
                        printf("ParseStartBoundry start ParseStartBoundryEnd trace1 \n");
                        mBoundaryEndLineIndex = 0;
                        reader->pop();
                        mStatus = ParseStartBoundry;
                        return part;
                    }
                    mBoundaryEndLineIndex++;
                } else {
                    printf("ParseStartBoundry start ParseStartBoundryEnd trace2 \n");
                    mBoundaryEndLineIndex = 0;
                }
            }
            break;

            case ParseContentDisposition: {
                printf("ParseStartBoundry start ParseContentDisposition start \n");
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == (NewLine->size()-1)) {
                        mNewLineTextIndex = 0;
                        
                        if(mContentDispositionBuff == nullptr) {
                            mContentDispositionBuff = reader->pop();
                        } else {
                            mContentDispositionBuff->append(reader->pop());
                        }
                        printf("mContentDispositionBuff->toString() is %s \n",mContentDispositionBuff->toString()->toChars());
                        mContentDisp = parseContentDisposition(mContentDispositionBuff->toString());
                        mContentDispositionBuff = nullptr;
                        mContentType = nullptr;
                        if(mContentDisp->dispositions->get("filename") != nullptr) {
                            printf("mContentDispositionBuff disposition is file");
                            mStatus = ParseContentType;
                        } else {
                            printf("mContentDispositionBuff disposition finished \n");
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
                printf("ParseStartBoundry start ParseContentDispositionEnd start \n");
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == (NewLine->size()-1)) {
                        mNewLineTextIndex = 0;
                        reader->pop();
                        mStatus = ParseContent;
                        continue;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContentType:{
                printf("ParseStartBoundry start ParseContentType start \n");
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == 1) {
                        mNewLineTextIndex = 0;
                        if(mContentTypeBuff == nullptr) {
                            mContentTypeBuff = reader->pop();
                        } else {
                            mContentTypeBuff->append(reader->pop());
                        }

                        mContentType = parseContentType(mContentTypeBuff->toString());
                        if(mContentType == nullptr || mContentType->size() == 0) {
                            mStatus = ParseStartBoundry;
                        } else {
                            mStatus = ParseContent;
                        }
                        continue;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContent:
                printf("ParseStartBoundry start ParseContent start,mBoundaryIndex is %d,mBoundaryStr is %s \n",mBoundaryIndex,mBoundaryStr);
                if(v == mBoundaryStr[mBoundaryIndex]) {
                    if(mBoundaryIndex == (mBoundary->size()-1)) {
                        //flush data
                        printf("ParseStartBoundry ParseContent trace1 \n");
                        mBoundaryIndex = 0;
                        ByteArray content = reader->pop();
                        content->quickShrink(content->size() - mBoundary->size());
                        printf("content is %s \n",content->toString()->toChars());
                        if(mContentType == nullptr) {
                            if(mContentBuff != nullptr) {
                                mContentBuff->append(content);
                            } else {
                                mContentBuff = content;
                            }

                            String value = mContentBuff->toString();
                            value = value->subString(0,content->size() - mBoundary->size()- NewLine->size());
                            String name = mContentDisp->dispositions->get(MultiPartNameTag);
                            HttpMultiPartContent block = createHttpMultiPartContent(name,value);
                            part->contents->add(block);

                            mContentDisp = nullptr;
                            mContentBuff = nullptr;
                        } else {
                            //hit complete flush file
                            printf("ParseStartBoundry ParseFile trace1 \n");
                            if(mFileStream == nullptr) {
                                String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                                String filename = mContentDisp->dispositions->get("filename");
                                mFile = createFile(filepath->append(filename));
                                printf("ParseStartBoundry ParseFile trace2 mFile path is %s\n",mFile->getAbsolutePath()->toChars());
                                mFile->createNewFile();
                                mFileStream = createFileOutputStream(mFile);
                                mFileStream->open();
                            } 
                            
                            if(mContentBuff == nullptr) {
                                mContentBuff = content;
                            } else {
                                mContentBuff->append(content);
                            }
                            printf("ParseStartBoundry ParseFile trace2 \n");
                            mContentBuff->quickShrink(mContentBuff->size() - mBoundary->size() - NewLine->size());
                            mFileStream->write(mContentBuff);
                            mFileStream->flush();
                            mFileStream->close();
                            mFileStream = nullptr;
                            mContentBuff = nullptr;
                            mContentType = nullptr;

                            HttpMultiPartFile file = createHttpMultiPartFile(mFile);
                            part->files->add(file);
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
                printf("check ParseContent trace1 \n");
                if(mContentType != nullptr) {
                    if(mFileStream == nullptr) {
                        String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                        String filename = mContentDisp->dispositions->get("filename");
                        mFileStream = createFileOutputStream(filepath->append(filename));
                        mFileStream->open();
                    }
                    printf("check ParseContent trace2 \n");

                    ByteArray content = reader->pop();
                    
                    content->quickShrink(content->size() - mBoundaryIndex);
                    if(mContentBuff != nullptr) {
                        mContentBuff->append(content);
                    } else {
                        mContentBuff = content;
                    }
                    printf("check ParseContent trace3 \n");
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

    return data;
}

}