#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpMultiPart.hpp"
#include "HttpUrl.hpp"
#include "String.hpp"
#include "UUID.hpp"
#include "HttpText.hpp"
#include "HttpMime.hpp"
#include "Enviroment.hpp"

namespace obotcha {

//-----------------HttpMultiPartFile-----------------
// _HttpMultiPartFile::_HttpMultiPartFile(File file,String k) {
//     mFile = file;
//     mKey = (k == nullptr)?file->getName():k;    
// }

_HttpMultiPartFile::_HttpMultiPartFile(String filename,String name,HttpHeaderContentType type) {

    String filepath = st(Enviroment)::getInstance()->get(
        st(Enviroment)::gHttpMultiPartFilePath);

    File dir = createFile(filepath);
    if (!dir->exists()) {
        dir->createDir();
    }

    UUID uuid = createUUID();
    while (1) {
        String mUuidFileName = uuid->generate();
        mFile = createFile(filepath->append(mUuidFileName));

        if (!mFile->exists()) {
            mFile->createNewFile();
            break;
        }
    }

    mName = name;
    mContentType = type;
    mOriginalFileName = filename;
}

//this construct function used by http client to create request;
_HttpMultiPartFile::_HttpMultiPartFile(File file,String name) {
    mName = name;

    String filename = file->getName();
    mFile = filename;
    mOriginalFileName= filename;

    mFile = file;
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

// String _HttpMultiPartFile::getKey() {
//     return mKey;
// }

// File _HttpMultiPartFile::getFile() {
//     return mFile;
// }

// String _HttpMultiPartFile::getFileName() {
//     return mFileName;
// }

//_HttpMultiPart();
_HttpMultiPart::_HttpMultiPart() {
    files = createArrayList<HttpMultiPartFile>();
    contents = createArrayList<Pair<String, String>>();

    UUID uuid = createUUID();
    mBoundary = uuid->generate()->replaceAll("-", "");
}

String _HttpMultiPart::getBoundary() {
    return mBoundary;
}


void _HttpMultiPart::addFile(File f,String name) {
    HttpMultiPartFile part = createHttpMultiPartFile(f,name);
    files->add(part);
}

void _HttpMultiPart::addContents(String name,String value) {
    contents->add(createPair<String,String>(name,value));
}


/*
*
\r\n ->did not compute in httpmultipart,but should add in compute all content length.
--===============0688100289==\r\n
Content-type: application/json\r\n
\r\n
{"title": "test-multipart.txt", "parents": [{"id":"0B09i2ZH5SsTHTjNtSS9QYUZqdTA"}], "properties": [{"kind": "drive#property", "key": "cloudwrapper", "value": "true"}]}\r\n
--===============0688100289==\r\n
Content-type: text/plain\r\n
\r\n
We're testing multipart uploading!\r\n
--===============0688100289==--
There are nine (9) lines, and I have manually added "\r\n" at the end of each of the first eight (8) lines (for readability reasons). Here are the number of octets (characters) in each line:

29 + '\r\n'
30 + '\r\n'
'\r\n'
167 + '\r\n'
29 + '\r\n'
24 + '\r\n'
'\r\n'
34 + '\r\n' (although '\r\n' is not part of the text file, Google inserts it)
31
The sum of the octets is 344, and considering each '\r\n' as a single one-octet sequence gives us the coveted content length of 344 + 8 = 352.
*
*/
long _HttpMultiPart::getContentLength() {
    long length = 0;

    //comput key/value length
    long keyValueLength = (mBoundary->size() 
                        + st(HttpText)::BoundaryBeginning->size() 
                        + st(HttpText)::BoundarySeperator->size()
                        + st(HttpText)::CRLF->size());
    
    keyValueLength += (st(HttpHeader)::ContentDisposition->size() + 2 /*": "*/
                    + st(HttpMime)::FormData->size() + 2    /*"; "*/
                    + st(HttpText)::MultiPartName->size() + 3      /*=""*/
                    + 0 /*key size*/ + st(HttpText)::CRLF->size());

    keyValueLength += st(HttpText)::CRLF->size();

    //get all keyValueLength except key/value length
    keyValueLength = keyValueLength *contents->size();

    ListIterator<Pair<String, String>> contentIterator = contents->getIterator();
    while (contentIterator->hasValue()) {
        Pair<String, String> content = contentIterator->getValue();
        keyValueLength += content->getKey()->size();
        keyValueLength += content->getValue()->size();
    }

    long fileContentLength = (mBoundary->size() 
                            + st(HttpText)::BoundaryBeginning->size() 
                            + st(HttpText)::BoundarySeperator->size()
                            + st(HttpText)::CRLF->size());

    fileContentLength += st(HttpHeader)::ContentDisposition->size() + 2 /*": "*/
                    + st(HttpMime)::FormData->size() + 2    /*"; "*/
                    + st(HttpText)::MultiPartName->size() + 5      /*=""; */
                    + 0 /*key size*/ + st(HttpText)::MultiPartFileName->size() + 3 /*=""*/
                    + 0 /*filename size*/ + st(HttpText)::CRLF->size();
    fileContentLength += st(HttpText)::CRLF->size();
    fileContentLength += st(HttpText)::CRLF->size();

    fileContentLength = fileContentLength*files->size();

    ListIterator<HttpMultiPartFile> fileIterator = files->getIterator();
    while (fileIterator->hasValue()) {
        HttpMultiPartFile content = fileIterator->getValue();
        fileContentLength += content->getName()->size();
        fileContentLength += content->getFile()->getName()->size();
        fileContentLength += content->getFile()->length();
        fileIterator->next();
    }

    length += fileContentLength;
    length += keyValueLength;

    length += (mBoundary->size() + 
            + st(HttpText)::BoundarySeperator->size()
            + st(HttpText)::BoundaryBeginning->size() * 2
            + st(HttpText)::CRLF->size()); //end
    printf("calc length is %d \n",length);
    return length;
}

}