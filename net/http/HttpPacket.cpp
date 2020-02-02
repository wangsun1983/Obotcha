#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

_HttpPacket::_HttpPacket() {
    mHeader = createHttpHeader();
	mMinorVer = 1;
	mMajorVer = 1;
}

void _HttpPacket::setHeader(HttpHeader h) {
    mHeader = h;
}

HttpHeader _HttpPacket::getHeader() {
	mHeader->setMethod(mMethod);
    return mHeader;
}
    
void _HttpPacket::setUrl(String url) {
    mUrl = url;
}

void _HttpPacket::setBody(ByteArray body) {
    mBody = body;
}

ByteArray _HttpPacket::getBody() {
	return mBody;
}

String _HttpPacket::getUrl() {
    return mUrl;
}

void _HttpPacket::setReason(String reason) {
    mReason = reason;
}

String _HttpPacket::getReason() {
    return mReason;
}

void _HttpPacket::setMethod(int v) {
    mMethod = v;
}

int _HttpPacket::getMethod() {
    return mMethod;
}

void _HttpPacket::setMajorVersion(int v) {
    mMajorVer = v;
}

int _HttpPacket::getMajorVersion() {
    return mMajorVer;
}

void _HttpPacket::setMinorVersion(int v) {
    mMinorVer = v;
}

int _HttpPacket::getMinorVersion() {
    return mMinorVer;
}

int _HttpPacket::getStatusCode() {
    return mStatusCode;
}

String _HttpPacket::getStatusString(int status) {
    switch(status) {
	    case 100: return createString("Continue");
 	    case 101: return createString("Switching Protocols");
 	    case 200: return createString("OK");
 	    case 201: return createString("Created");
 	    case 202: return createString("Accepted");
 	    case 203: return createString("Non-Authoritative Information");
 	    case 204: return createString("No Content");
 	    case 205: return createString("Reset Content");
 	    case 206: return createString("Partial Content");
 	    case 300: return createString("Multiple Choices");
 	    case 301: return createString("Moved Permanently");
 	    case 302: return createString("Found");
 	    case 303: return createString("See Other");
 	    case 304: return createString("Not Modified");
 	    case 305: return createString("Use Proxy");
 	    case 307: return createString("Temporary Redirect");
 	    case 400: return createString("Bad Request");
 	    case 401: return createString("Unauthorized");
 	    case 402: return createString("Payment Required");
 	    case 403: return createString("Forbidden");
 	    case 404: return createString("Not Found");
 	    case 405: return createString("Method Not Allowed");
 	    case 406: return createString("Not Acceptable");
 	    case 407: return createString("Proxy Authentication Required");
 	    case 408: return createString("Request Time-out");
 	    case 409: return createString("Conflict");
 	    case 410: return createString("Gone");
 	    case 411: return createString("Length Required");
 	    case 412: return createString("Precondition Failed");
 	    case 413: return createString("Request Entity Too Large");
 	    case 414: return createString("Request-URI Too Large");
 	    case 415: return createString("Unsupported Media Type");
 	    case 416: return createString("Requested range not satisfiable");
 	    case 417: return createString("Expectation Failed");
 	    case 500: return createString("Internal Server Error");
 	    case 501: return createString("Not Implemented");
 	    case 502: return createString("Bad Gateway");
 	    case 503: return createString("Service Unavailable");
 	    case 504: return createString("Gateway Time-out");
 	    case 505: return createString("HTTP Version not supported");
	    default:  return createString("Unknown");
	}
}

void _HttpPacket::setStatusCode(int v) {
    mStatusCode = v;
}

String _HttpPacket::genHttpRequest() {
    String req = createString();
    switch(mMethod) {
        case HttpMethodGet:
        req = createString("GET");
        break;

        case HttpMethodPost:
        req = createString("POST");
        break;

        default:
        return nullptr;
    }

    req = req->append(" ")
             ->append(mUrl)
             ->append(" HTTP/")
             ->append(createString(mMajorVer))
             ->append(".")
             ->append(createString(mMinorVer))
             ->append("\r\n");

    req = req->append(mHeader->genHtml());

    req = req->append("\r\n\r\n");

    return req;   
}

String _HttpPacket::genHttpResponse() {
    String statusString = mHeader->getValue(st(HttpHeader)::Status);
	if(statusString == nullptr) {
		return nullptr;
	}

	//printf("statusString is %s \n",statusString->toChars());
    
	String status = getStatusString(statusString->toBasicInt());
	String responseStr = createString("HTTP/1.1 ")->append(statusString)->append(" ")->append(status)->append("\r\n");
    
	String headerStr =mHeader->genHtml();
	String bodyStr = createString((char *)mBody->toValue(),0,mBody->size());
	
	responseStr = responseStr->append(headerStr)->append("\r\n")->append(bodyStr);
    return responseStr;
}

void _HttpPacket::dump() {
    //MapIterator<int,String> getIterator();
	MapIterator<String,String> iterator = mHeader->getIterator();
	while(iterator->hasValue()) {
		String key = iterator->getKey();
		String value = iterator->getValue();
        printf("[%s]:%s \n",key->toChars(),value->toChars());
		iterator->next();
	}

	//dump body
	if(mBody != nullptr) {
		printf("body is %s \n",mBody->toString()->toChars());
	} else {
		printf("body is null \n");
	}
}

}

