#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpResponse.hpp"

using namespace obotcha;

String _HttpResponse::getStatusString(int status){
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