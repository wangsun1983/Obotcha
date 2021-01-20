#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"

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
    //start parse boundary
    ArrayList<String> strings = contenttype->split(";");
    if(strings == nullptr || strings->size() == 0) {
        Trigger(InitializeException,"MultiPartParser init fail!!");
    }

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
    mFileStream = nullptr;
    mHttpFile = nullptr;
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
    //HttpMultiPart part = createHttpMultiPart();
    if(mMultiPart == nullptr) {
        mMultiPart = createHttpMultiPart();
    }

    while(reader->readNext(v) == ByteRingArrayReadContinue) {
        switch(mStatus) {
            case ParseStartBoundry:{
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
                if(v == mNewLineStr[mBoundaryEndLineIndex]) {
                    if(mBoundaryEndLineIndex == (NewLine->size()-1)) {
                        mBoundaryEndLineIndex = 0;
                        reader->pop();
                        mStatus = ParseContentDisposition;
                        continue;
                    }
                    mBoundaryEndLineIndex++;
                } else if(v == mEndLineStr[mBoundaryEndLineIndex]){
                    if(mBoundaryEndLineIndex == (EndLine->size()-1)) {
                        mBoundaryEndLineIndex = 0;
                        reader->pop();
                        mStatus = ParseStartBoundry;
                        HttpMultiPart part = mMultiPart;
                        mMultiPart = nullptr;
                        return part;
                    }
                    mBoundaryEndLineIndex++;
                } else {
                    mBoundaryEndLineIndex = 0;
                }
            }
            break;

            case ParseContentDisposition: {
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == (NewLine->size()-1)) {
                        mNewLineTextIndex = 0;
                        
                        if(mContentDispositionBuff == nullptr) {
                            mContentDispositionBuff = reader->pop();
                        } else {
                            mContentDispositionBuff->append(reader->pop());
                        }
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

            case ParseContentDispositionEnd:
            case ParseContentSkipNewLine: {
                if(v == mNewLineStr[mNewLineTextIndex]) {
                    if(mNewLineTextIndex == 1) {
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
                            mStatus = ParseContent;
                        } else {
                            mStatus = ParseContentSkipNewLine;
                        }
                        continue;
                    }
                    mNewLineTextIndex++;
                } else {
                    mNewLineTextIndex = 0;
                }
            }
            break;

            case ParseContent: {
                if(v == mBoundaryStr[mBoundaryIndex]) {
                    if(mBoundaryIndex == (mBoundary->size()-1)) {
                        //flush data
                        mBoundaryIndex = 0;
                        ByteArray content = reader->pop();
                        int shrinkSize = (content->size() - mBoundary->size());
                        if(shrinkSize == 0) {
                            content = nullptr;
                        } else {
                            content->quickShrink(shrinkSize);
                        }

                        if(mContentType == nullptr) {
                            if(mContentBuff != nullptr) {
                                mContentBuff->append(content);
                            } else {
                                mContentBuff = content;
                            }
                           
                            if(mContentBuff != nullptr) {
                                String value = mContentBuff->toString();
                                value = value->subString(0,value->size()- NewLine->size());
                                String name = mContentDisp->dispositions->get(MultiPartNameTag);
                                HttpMultiPartContent block = createHttpMultiPartContent(name,value);
                                mMultiPart->contents->add(block);
                            }
                            
                            mContentDisp = nullptr;
                            mContentBuff = nullptr;
                        } else {
                            //hit complete flush file
                            if(mFileStream == nullptr) {
#if 0
                                String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                                String filename = mContentDisp->dispositions->get("filename");
                                mFile = createFile(filepath->append(filename));
                                String name = mFile->getNameWithNoSuffix();
                                String suffix = mFile->getSuffix();
                                while(mFile->exists()) {
                                    String newName = name->append("_",createString(st(System)::currentTimeMillis()),suffix);
                                    mFile = createFile(filepath->append(newName));
                                }

                                mFile->createNewFile();
#endif
                                String filename = mContentDisp->dispositions->get("filename");
                                mHttpFile = createHttpFile(filename);
                                File file = mHttpFile->getFile();
                                mFileStream = createFileOutputStream(file);
                                mFileStream->open();
                            } 
                            
                            if(mContentBuff == nullptr) {
                                mContentBuff = content;
                            } else {
                                mContentBuff->append(content);
                            }
                           
                            if(mContentBuff != nullptr) {
                                mContentBuff->quickShrink(mContentBuff->size() - NewLine->size());
                                mFileStream->write(mContentBuff);
                            }

                            mFileStream->flush();
                            mFileStream->close();

                            HttpMultiPartFile file = createHttpMultiPartFile(mHttpFile);
                            mMultiPart->files->add(file);
                            mFileStream = nullptr;
                            mContentBuff = nullptr;
                            mContentType = nullptr;
                            mContentTypeBuff = nullptr;
                        }
                        mStatus = ParseStartBoundryEnd;
                        continue;
                    }
                    mBoundaryIndex++;
                } else {
                    mBoundaryIndex = 0;
                }
            }
            break;

            default: {
                LOG(ERROR)<<"HttpMultiPartParser error status is "<<mStatus;
            }
        }
    }
    
    //check whether there is no analyze buff
    if(reader->getReadableLength() != 0) {
        switch(mStatus) {
            case ParseStartBoundry:{
                reader->pop();
            }
            break;

            case ParseStartBoundryEnd:
            case ParseContentSkipNewLine:{
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
                    if(mFileStream == nullptr) {
#if 0
                        String filepath = mEnv->get(st(Enviroment)::gHttpMultiPartFilePath);
                        printf("filepath is %s \n",filepath->toChars());
                        File dir = createFile(filepath);
                        dir->createDirs();
                        
                        String filename = mContentDisp->dispositions->get("filename");
                        printf("filename is %s \n",filename->toChars());
                        mFile = createFile(filepath->append(filename));
                        String name = mFile->getNameWithNoSuffix();
                        String suffix = mFile->getSuffix();
                        while(mFile->exists()) {
                            String newName = name->append("_",createString(st(System)::currentTimeMillis()),suffix);
                            mFile = createFile(filepath->append(newName));
                        }
                        mFile->createNewFile();
                        mFileStream = createFileOutputStream(mFile);
                        mFileStream->open();
#endif
                        String filename = mContentDisp->dispositions->get("filename");
                        mHttpFile = createHttpFile(filename);
                        File file = mHttpFile->getFile();
                        mFileStream = createFileOutputStream(file);
                        mFileStream->open();
                    }
                    if(mBoundaryIndex == 0) {
                        ByteArray content = reader->pop();
                        if(content != nullptr) {
                            content->quickShrink(content->size() - mBoundaryIndex);
                            if(mContentBuff != nullptr) {
                                mContentBuff->append(content);
                            } else {
                                mContentBuff = content;
                            }
                            mFileStream->write(mContentBuff);
                            mFileStream->flush();
                            mContentBuff = nullptr;
                        }
                    }
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
    if(split != nullptr) {
        ListIterator<String> iterator = split->getIterator();
        while(iterator->hasValue()) {
            iterator->next();
        }
        
    }
    if(split == nullptr || split->size() != 2) {
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