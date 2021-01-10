#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpRequestWriter.hpp"
#include "HttpContentType.hpp"
#include "HttpHeader.hpp"
#include "Log.hpp"
#include "UUID.hpp"
#include "HttpText.hpp"

namespace obotcha {

_HttpRequestWriter::_HttpRequestWriter(TcpClient c) {
    mTcpClient = c;
}

int _HttpRequestWriter::write(HttpRequest p) {
    //1.create head
    String req = createString(); 
    switch(p->getMethod()) {
        case st(HttpMethod)::Get:
        req = createString("GET");
        break;

        case st(HttpMethod)::Post:
        req = createString("POST");
        break;
        
        case st(HttpMethod)::Put:
        req = createString("PUT");
        break;
        
        case st(HttpMethod)::Delete:
        req = createString("DELETE");
        break;

        default:
        LOG(ERROR)<<"unsupport request type";
        return -1;
    }

    String contentType = p->getHeader(st(HttpHeader)::ContentType);
    String boundary = generateMultiPartBoundary();
    contentType = contentType->append(st(HttpContentType)::MultiPartFormData,";","boundary=",boundary);
    p->setHeader(st(HttpHeader)::ContentType,contentType);

    req = req->append(" ",p->getUrl()->toString(),
                      " HTTP/",createString(p->getMajorVersion()),".",createString(p->getMinorVersion()),
                      "\r\n",
                      p->mPacket->getHeader()->toString(),
                      st(HttpText)::LineEnd);

    //2. compose body
    HttpMultiPart multiPart = p->mPacket->getMultiPart();
    String boundTag = createString(st(HttpText)::BoundaryBeginning)->append(st(HttpText)::BoundarySeperator,boundary);

    if(multiPart != nullptr) {
        ListIterator<HttpMultiPartContent> iterator = multiPart->contents->getIterator();
        while(iterator->hasValue()) {
            HttpMultiPartContent content = iterator->getValue();
            req = req->append(boundTag,st(HttpText)::LineEnd);
            req = req->append(st(HttpHeader)::ContentDisposition,": ",st(HttpContentType)::FormData,"; ",
                        st(HttpText)::PartName,createString('="'),content->getName(),createString('="'),
                        st(HttpText)::LineEnd);
            req = req->append(st(HttpText)::LineEnd);
            req = req->append(content->getValue(),st(HttpText)::LineEnd);
        }
    }
    
}

String _HttpRequestWriter::generateMultiPartBoundary() {
    UUID uuid = createUUID();
    String boundary = uuid->generate();
    String tag = createString("--------------------------");
    return tag->append(boundary->replaceAll("-",""));
}


}
