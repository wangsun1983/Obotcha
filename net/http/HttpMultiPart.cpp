#include "HttpMultiPart.hpp"
#include "UUID.hpp"
#include "HttpText.hpp"
#include "HttpMime.hpp"
#include "HttpHeader.hpp"
#include "FileInputStream.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartFile::_HttpMultiPartFile(String filename,
                                      String name,HttpHeaderContentType type):
                                      mName(name),
                                      mOriginalFileName(filename),
                                      mContentType(type) {

    String filepath = st(Http)::Config::kMultiPartDirectory;

    if (File dir = createFile(filepath);!dir->exists()) {
        dir->createDir();
    }

    UUID uuid = createUUID();
    InfiniteLoop {
        String mUuidFileName = uuid->generate();
        mFile = createFile(filepath->append(mUuidFileName));

        if (!mFile->exists()) {
            mFile->createNewFile();
            break;
        }
    }

    if(mContentType == nullptr) {
        String suffix = mFile->getSuffix();
        updateContentType(suffix);
    }
}

//this construct function used by http client to create request;
_HttpMultiPartFile::_HttpMultiPartFile(File file,String name,HttpHeaderContentType type):
                                      mFile(file),mName(name),mContentType(type) {
    String filename = file->getName();
    mOriginalFileName= filename;
    if(mContentType == nullptr) {
        String suffix = mFile->getSuffix();
        updateContentType(suffix);
    }
}

void _HttpMultiPartFile::updateContentType(String suffix) {
    HttpMime mime = createHttpMime()->setSuffix(suffix);
    String name = mime->getType();
    if(name == nullptr) {
        name = st(HttpMime)::MultiPartFormData;
    }
    mContentType = createHttpHeaderContentType(name);
}

String _HttpMultiPartFile::getName() {
    return mName;
}

String _HttpMultiPartFile::getOriginalFileName() {
    return mOriginalFileName;
}

HttpHeaderContentType _HttpMultiPartFile::getContentType() {
    return mContentType;
}

File _HttpMultiPartFile::getFile() {
    return mFile;
}

_HttpMultiPart::_HttpMultiPart() {
    UUID uuid = createUUID();
    mBoundary = uuid->generate()->replaceAll("-", "");
}

_HttpMultiPart::_HttpMultiPart(String boundary):mBoundary(boundary) {
}

ArrayList<HttpMultiPartFile> _HttpMultiPart::getFiles() {
    return files;
}

ArrayList<Pair<String, String>> _HttpMultiPart::getContents() {
    return contents;
}

String _HttpMultiPart::getBoundary() {
    return mBoundary;
}


void _HttpMultiPart::addFile(File f,String name) {
    HttpMultiPartFile part = createHttpMultiPartFile(f,name);
    files->add(part);
}

void _HttpMultiPart::addFile(HttpMultiPartFile file) {
    files->add(file);
}

void _HttpMultiPart::addContent(String name,String value) {
    contents->add(createPair<String,String>(name,value));
}


long _HttpMultiPart::getContentLength() {
    long length = 0;

    //comput key/value length
    long keyValueLength = 0;
    long fileContentLength = 0;

    if(contents->size() != 0) {
        keyValueLength = st(HttpText)::MultiPartContentTemplate->size() 
                         - 3*2 /*three %s*/
                         + mBoundary->size();
        keyValueLength = keyValueLength *contents->size();

        ArrayListIterator<Pair<String, String>> contentIterator = contents->getIterator();
        while (contentIterator->hasValue()) {
            Pair<String, String> content = contentIterator->getValue();
            keyValueLength += content->getKey()->size();
            keyValueLength += content->getValue()->size();
            contentIterator->next();
        }
    }

    if(files->size() != 0) {
        fileContentLength = st(HttpText)::MultiPartFileTemplate->size() 
                            - 4*2
                            + mBoundary->size();
        fileContentLength = fileContentLength*files->size();
        ArrayListIterator<HttpMultiPartFile> fileIterator = files->getIterator();
        while (fileIterator->hasValue()) {
            HttpMultiPartFile content = fileIterator->getValue();
            fileContentLength += content->getName()->size();
            fileContentLength += content->getFile()->getName()->size();
            fileContentLength += content->getFile()->length();
            fileContentLength += content->getContentType()->toString()->size();
            fileIterator->next();
        }
    }

    length += fileContentLength;
    length += keyValueLength;

    length += st(HttpText)::MultiPartEndTemplate->size() 
              + mBoundary->size() - 2; //end
    return length;
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
void _HttpMultiPart::onCompose(const ComposeCallBack &callback) {
    if (contents->size() > 0) {
        ArrayListIterator<Pair<String, String>> iterator = contents->getIterator();
        while (iterator->hasValue()) {
            Pair<String, String> content = iterator->getValue();
            String v = st(String)::Format(st(HttpText)::MultiPartContentTemplate->toChars(),
                                          mBoundary->toChars(),
                                          content->getKey()->toChars(),
                                          content->getValue()->toChars());
            callback(v->toByteArray());
            iterator->next();
        }
    }
        
    if (files->size() > 0) {
        ArrayListIterator<HttpMultiPartFile> iterator = files->getIterator();

        while (iterator->hasValue()) {
            HttpMultiPartFile partFile = iterator->getValue();
            String v = st(String)::Format(st(HttpText)::MultiPartFileTemplate->toChars(),
                                        mBoundary->toChars(),
                                        partFile->getName()->toChars(),
                                        partFile->getFile()->getName()->toChars(),
                                        partFile->getContentType()->toString()->toChars());
            callback(v->toByteArray());

            FileInputStream stream = createFileInputStream(partFile->getFile());
            stream->open();
            ByteArray readBuff = createByteArray(1024*32);
            long readSize = 0;
            while ((readSize = stream->read(readBuff)) > 0) {
                readBuff->quickShrink(readSize);
                callback(readBuff);
                readBuff->quickRestore();
            }

            callback(st(HttpText)::CRLF->toByteArray());
            iterator->next();
        }
    }
        
    String finish = st(String)::Format(st(HttpText)::MultiPartEndTemplate->toChars(),
                                        mBoundary->toChars());
    callback(finish->toByteArray());
}

}