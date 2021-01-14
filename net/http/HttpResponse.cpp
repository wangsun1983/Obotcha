#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpResponse.hpp"

namespace obotcha {

const int _HttpResponse::Continue = 100;
const int _HttpResponse::SwitchProtocls = 101;
const int _HttpResponse::Ok = 200;
const int _HttpResponse::Created = 201;
const int _HttpResponse::Accepted = 202;
const int _HttpResponse::NonAuthoritativeInformation = 203;
const int _HttpResponse::NoContent = 204;
const int _HttpResponse::ResetContent = 205;
const int _HttpResponse::PartialContent = 206;
const int _HttpResponse::MultipleChoices = 300;
const int _HttpResponse::MovedPermanently = 301;
const int _HttpResponse::Found = 302;
const int _HttpResponse::SeeOther = 303;
const int _HttpResponse::NotModified = 304;
const int _HttpResponse::UseProxy = 305;
//const int _HttpResponse::UnUsed = 306;
const int _HttpResponse::TemporaryRedirect = 307;
const int _HttpResponse::BadRequest = 400;
const int _HttpResponse::Unauthorized = 401;
const int _HttpResponse::PaymentRequired = 402;
const int _HttpResponse::Forbidden = 403;
const int _HttpResponse::NotFound = 404;
const int _HttpResponse::MethodNotAllowed = 405;
const int _HttpResponse::NotAcceptable = 406;
const int _HttpResponse::ProxyAuthenticationRequired = 407;
const int _HttpResponse::RequestTimeTou = 408;
const int _HttpResponse::Conflict = 409;
const int _HttpResponse::Gone = 410;
const int _HttpResponse::LengthRequired = 411;
const int _HttpResponse::PreconditionFailed = 412;
const int _HttpResponse::RequestEntityToLarge = 413;
const int _HttpResponse::RequestUriTooLarge = 414;
const int _HttpResponse::UnsupportedMediaType = 415;
const int _HttpResponse::RequestedRangeNotSatisfiable = 416;
const int _HttpResponse::ExpectationFailed = 417;
const int _HttpResponse::InternalServerError = 500;
const int _HttpResponse::NotImplemented = 501;
const int _HttpResponse::BadGateway = 502;
const int _HttpResponse::ServiceUnavailable = 503;
const int _HttpResponse::GatewayTimeOut = 504;
const int _HttpResponse::VersionNotSupported = 505;

String _HttpResponse::castStatus(int status){
    switch(status) {
	    case Continue: return createString("Continue");
 	    case SwitchProtocls: return createString("Switching Protocols");
 	    case Ok: return createString("OK");
 	    case Created: return createString("Created");
 	    case Accepted: return createString("Accepted");
 	    case NonAuthoritativeInformation: return createString("Non-Authoritative Information");
 	    case NoContent: return createString("No Content");
 	    case ResetContent: return createString("Reset Content");
 	    case PartialContent: return createString("Partial Content");
 	    case MultipleChoices: return createString("Multiple Choices");
 	    case MovedPermanently: return createString("Moved Permanently");
 	    case Found: return createString("Found");
 	    case SeeOther: return createString("See Other");
 	    case NotModified: return createString("Not Modified");
 	    case UseProxy: return createString("Use Proxy");
 	    case TemporaryRedirect: return createString("Temporary Redirect");
 	    case BadRequest: return createString("Bad Request");
 	    case Unauthorized: return createString("Unauthorized");
 	    case PaymentRequired: return createString("Payment Required");
 	    case Forbidden: return createString("Forbidden");
 	    case NotFound: return createString("Not Found");
 	    case MethodNotAllowed: return createString("Method Not Allowed");
 	    case NotAcceptable: return createString("Not Acceptable");
 	    case ProxyAuthenticationRequired: return createString("Proxy Authentication Required");
 	    case RequestTimeTou: return createString("Request Time-out");
 	    case Conflict: return createString("Conflict");
 	    case Gone: return createString("Gone");
 	    case LengthRequired: return createString("Length Required");
 	    case PreconditionFailed: return createString("Precondition Failed");
 	    case RequestEntityToLarge: return createString("Request Entity Too Large");
 	    case RequestUriTooLarge: return createString("Request-URI Too Large");
 	    case UnsupportedMediaType: return createString("Unsupported Media Type");
 	    case RequestedRangeNotSatisfiable: return createString("Requested range not satisfiable");
 	    case ExpectationFailed: return createString("Expectation Failed");
 	    case InternalServerError: return createString("Internal Server Error");
 	    case NotImplemented: return createString("Not Implemented");
 	    case BadGateway: return createString("Bad Gateway");
 	    case ServiceUnavailable: return createString("Service Unavailable");
 	    case GatewayTimeOut: return createString("Gateway Time-out");
 	    case VersionNotSupported: return createString("HTTP Version not supported");
	    default:  return createString("Unknown");
	}
}

_HttpResponse::_HttpResponse(HttpPacket packet) {
	mPacket = packet;
}

_HttpResponse::_HttpResponse() {
	mPacket = createHttpPacket();
}

int _HttpResponse::getStatus() {
	return mPacket->getStatusCode();
}

ByteArray _HttpResponse::getBody() {
	return mPacket->getBody();
}

String _HttpResponse::getHeader(String key) {
	return mPacket->getHeader()->getValue(key);
}

void _HttpResponse::setBody(ByteArray) {
    //TODO
}

void _HttpResponse::setHeader(String,String) {
	//TODO
}

HttpHeader _HttpResponse::getHeaders() {
	return nullptr;
}

void _HttpResponse::setFile(File) {
	//TODO
}

void _HttpResponse::addCookie(HttpCookie) {
	//TODO
}


}