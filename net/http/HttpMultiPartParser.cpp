#include "HttpMultiPartParser.hpp"
#include "Enviroment.hpp"
#include "HttpText.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpMultiPartParser::_HttpMultiPartParser(const String &contenttype,
                                           int length) {
    mContentLength = length;
    // mBoundaryHeader = contenttype;
    // start parse boundary
    ArrayList<String> strings = contenttype->split(";");
    if (strings == nullptr || strings->size() == 0) {
        Trigger(InitializeException, "MultiPartParser init fail!!");
    }

    ListIterator<String> iterator = strings->getIterator();

    while (iterator->hasValue()) {
        String v = iterator->getValue();
        if (v->indexOfIgnoreCase(st(HttpText)::Boundary) == -1) {
            iterator->next();
            continue;
        }

        ArrayList<String> sp = v->split("=");
        if (sp->size() == 2) {
            mBoundary = sp->get(1);
            String start = createString("--");
            mBoundary = start->append(mBoundary);
            Boundary = mBoundary->toChars();
            break;
        }

        iterator->next();
    }

    mStatus = ParseStartBoundry;

    mEnv = st(Enviroment)::getInstance();

    CRLF = st(HttpText)::CRLF->toChars();
    MultiPartEnd = st(HttpText)::MultiPartEnd->toChars();

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
            printf("ParseStartBoundry start \n");
            if (v == Boundary[mBoundaryIndex]) {
                if (mBoundaryIndex == (mBoundary->size() - 1)) {
                    mBoundaryIndex = 0;
                    reader->pop();
                    mStatus = ParseStartBoundryEnd;
                }
                mBoundaryIndex++;
            } else {
                mBoundaryIndex = 0;
            }
            continue;
        } break;

        case ParseStartBoundryEnd: {
            printf("ParseStartBoundryEnd start \n");
            if (v == CRLF[mBoundaryEndLineIndex]) {
                if (mBoundaryEndLineIndex == (st(HttpText)::CRLF->size() - 1)) {
                    mBoundaryEndLineIndex = 0;
                    reader->pop();
                    mStatus = ParseContentDisposition;
                    continue;
                }
                mBoundaryEndLineIndex++;
            } else if (v == MultiPartEnd[mBoundaryEndLineIndex]) {
                if (mBoundaryEndLineIndex ==
                    (st(HttpText)::MultiPartEnd->size() - 1)) {
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
        } break;

        case ParseContentDisposition: {
            printf("ParseContentDisposition start \n");
            if (v == CRLF[mNewLineTextIndex]) {
                if (mNewLineTextIndex == (st(HttpText)::CRLF->size() - 1)) {
                    mNewLineTextIndex = 0;

                    if (mContentDispositionBuff == nullptr) {
                        mContentDispositionBuff = reader->pop();
                    } else {
                        mContentDispositionBuff->append(reader->pop());
                    }
                    mContentDisp = parseContentDisposition(
                        mContentDispositionBuff->toString());
                    mContentDispositionBuff = nullptr;
                    mContentType = nullptr;
                    if (mContentDisp->get(st(HttpText)::MultiPartFileName) !=
                        nullptr) {
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
        } break;

        case ParseContentDispositionEnd:
        case ParseContentSkipNewLine: {
            printf("ParseContentDispositionEnd start \n");
            if (v == CRLF[mNewLineTextIndex]) {
                if (mNewLineTextIndex == 1) {
                    mNewLineTextIndex = 0;
                    reader->pop();
                    mStatus = ParseContent;
                    continue;
                }
                mNewLineTextIndex++;
            } else {
                mNewLineTextIndex = 0;
            }
        } break;

        case ParseContentType: {
            printf("ParseContentType start \n");
            if (v == CRLF[mNewLineTextIndex]) {
                if (mNewLineTextIndex == 1) {
                    mNewLineTextIndex = 0;
                    if (mContentTypeBuff == nullptr) {
                        mContentTypeBuff = reader->pop();
                    } else {
                        mContentTypeBuff->append(reader->pop());
                    }
                    mContentType =
                        parseContentType(mContentTypeBuff->toString());
                    if (mContentType == nullptr || mContentType->size() == 0) {
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
        } break;

        case ParseContent: {
            // printf("ParseContent start,v is %x \n",v);
            if (v == Boundary[mBoundaryIndex]) {
                if (mBoundaryIndex == (mBoundary->size() - 1)) {
                    // flush data
                    mBoundaryIndex = 0;
                    ByteArray content = reader->pop();
                    int shrinkSize = (content->size() - mBoundary->size());
                    if (shrinkSize == 0) {
                        content = nullptr;
                    } else {
                        content->quickShrink(shrinkSize);
                    }

                    if (mContentType == nullptr) {
                        printf("ParseContent trace1 \n");
                        if (mContentBuff != nullptr) {
                            mContentBuff->append(content);
                        } else {
                            mContentBuff = content;
                        }

                        if (mContentBuff != nullptr) {
                            String value = mContentBuff->toString();
                            value = value->subString(
                                0, value->size() - st(HttpText)::CRLF->size());
                            String name =
                                mContentDisp->get(st(HttpText)::MultiPartName);
                            mMultiPart->contents->add(
                                createKeyValuePair<String, String>(name,
                                                                   value));
                        }

                        mContentDisp = nullptr;
                        mContentBuff = nullptr;
                    } else {
                        // hit complete flush file
                        printf("ParseContent trace2 \n");
                        if (mFileStream == nullptr) {
                            String filename = mContentDisp->get(
                                st(HttpText)::MultiPartFileName);
                            mHttpFile = createHttpFile(filename);
                            File file = mHttpFile->getFile();
                            mFileStream = createFileOutputStream(file);
                            mFileStream->open();
                        }

                        if (mContentBuff == nullptr) {
                            mContentBuff = content;
                        } else {
                            mContentBuff->append(content);
                        }

                        if (mContentBuff != nullptr) {
                            mContentBuff->quickShrink(
                                mContentBuff->size() -
                                st(HttpText)::CRLF->size());
                            printf("ParseContent contentbuff size is %d \n",
                                   mContentBuff->size());
                            mFileStream->write(mContentBuff);
                        }

                        mFileStream->flush();
                        mFileStream->close();

                        HttpMultiPartFile file =
                            createHttpMultiPartFile(mHttpFile);
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
        } break;

        default: {
            LOG(ERROR) << "HttpMultiPartParser error status is " << mStatus;
        }
        }
    }

    // check whether there is no analyze buff
    if (reader->getReadableLength() != 0) {
        switch (mStatus) {
        case ParseStartBoundry: {
            reader->pop();
        } break;

        case ParseStartBoundryEnd:
        case ParseContentSkipNewLine: {
            reader->pop();
        } break;

        case ParseContentDisposition: {
            if (mContentDispositionBuff == nullptr) {
                mContentDispositionBuff = reader->pop();
            } else {
                mContentDispositionBuff->append(reader->pop());
            }
        } break;

        case ParseContentDispositionEnd: {
            reader->pop();
        } break;

        case ParseContentType: {
            if (mContentTypeBuff == nullptr) {
                mContentTypeBuff = reader->pop();
            } else {
                mContentTypeBuff->append(reader->pop());
            }
        } break;

        case ParseContent: {
            if (mContentType != nullptr) {
                if (mFileStream == nullptr) {
                    String filename =
                        mContentDisp->get(st(HttpText)::MultiPartFileName);
                    mHttpFile = createHttpFile(filename);
                    File file = mHttpFile->getFile();
                    mFileStream = createFileOutputStream(file);
                    mFileStream->open();
                }
                if (mBoundaryIndex == 0) {
                    ByteArray content = reader->pop();
                    if (content != nullptr) {
                        content->quickShrink(content->size() - mBoundaryIndex);
                        if (mContentBuff != nullptr) {
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
                if (mContentBuff != nullptr) {
                    mContentBuff->append(reader->pop());
                } else {
                    mContentBuff = reader->pop();
                }
            }
        } break;
        }
    }

    return nullptr;
}

String _HttpMultiPartParser::parseContentType(String content) {
    ArrayList<String> split = content->split(":");
    if (split != nullptr) {
        ListIterator<String> iterator = split->getIterator();
        while (iterator->hasValue()) {
            iterator->next();
        }
    }
    if (split == nullptr || split->size() != 2) {
        return nullptr;
    }

    String type = split->get(1);
    return type->trimAll();
}

// Content-Disposition: form-data;name="file";filename="chrome.png"
HashMap<String, String>
_HttpMultiPartParser::parseContentDisposition(String position) {
    HashMap<String, String> data = createHashMap<String, String>();
    ArrayList<String> split1 = position->split(";");
    ListIterator<String> iterator1 = split1->getIterator();
    while (iterator1->hasValue()) {
        String tag = iterator1->getValue();
        ArrayList<String> split2 = tag->split(":");
        if (split2 == nullptr) {
            split2 = tag->split("=");
        }

        if (split2 != nullptr && split2->size() == 2) {
            String tag = split2->get(0)->trimAll();
            String value = split2->get(1)->trimAll();
            if (value->charAt(0) == '"') {
                int next = value->size() - 1;
                while (next != 0) {
                    if (value->charAt(next) == '"') {
                        break;
                    }

                    next--;
                }

                value = value->subString(1, next - 1);
            }

            data->put(tag, value);
        }

        iterator1->next();
    }

    return data;
}

} // namespace obotcha