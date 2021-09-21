#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpStatus.hpp"
#include "String.hpp"

namespace obotcha {

const int _HttpStatus::Continue = 100;
const int _HttpStatus::SwitchProtocls = 101;
const int _HttpStatus::Ok = 200;
const int _HttpStatus::Created = 201;
const int _HttpStatus::Accepted = 202;
const int _HttpStatus::NonAuthoritativeInformation = 203;
const int _HttpStatus::NoContent = 204;
const int _HttpStatus::ResetContent = 205;
const int _HttpStatus::PartialContent = 206;
const int _HttpStatus::MultipleChoices = 300;
const int _HttpStatus::MovedPermanently = 301;
const int _HttpStatus::Found = 302;
const int _HttpStatus::SeeOther = 303;
const int _HttpStatus::NotModified = 304;
const int _HttpStatus::UseProxy = 305;
// const int _HttpStatus::UnUsed = 306;
const int _HttpStatus::TemporaryRedirect = 307;
const int _HttpStatus::BadRequest = 400;
const int _HttpStatus::Unauthorized = 401;
const int _HttpStatus::PaymentRequired = 402;
const int _HttpStatus::Forbidden = 403;
const int _HttpStatus::NotFound = 404;
const int _HttpStatus::MethodNotAllowed = 405;
const int _HttpStatus::NotAcceptable = 406;
const int _HttpStatus::ProxyAuthenticationRequired = 407;
const int _HttpStatus::RequestTimeTou = 408;
const int _HttpStatus::Conflict = 409;
const int _HttpStatus::Gone = 410;
const int _HttpStatus::LengthRequired = 411;
const int _HttpStatus::PreconditionFailed = 412;
const int _HttpStatus::RequestEntityToLarge = 413;
const int _HttpStatus::RequestUriTooLarge = 414;
const int _HttpStatus::UnsupportedMediaType = 415;
const int _HttpStatus::RequestedRangeNotSatisfiable = 416;
const int _HttpStatus::ExpectationFailed = 417;
const int _HttpStatus::InternalServerError = 500;
const int _HttpStatus::NotImplemented = 501;
const int _HttpStatus::BadGateway = 502;
const int _HttpStatus::ServiceUnavailable = 503;
const int _HttpStatus::GatewayTimeOut = 504;
const int _HttpStatus::VersionNotSupported = 505;

String _HttpStatus::toString(int status) {
    switch (status) {
    case Continue:
        return createString("Continue");
    case SwitchProtocls:
        return createString("Switching Protocols");
    case Ok:
        return createString("OK");
    case Created:
        return createString("Created");
    case Accepted:
        return createString("Accepted");
    case NonAuthoritativeInformation:
        return createString("Non-Authoritative Information");
    case NoContent:
        return createString("No Content");
    case ResetContent:
        return createString("Reset Content");
    case PartialContent:
        return createString("Partial Content");
    case MultipleChoices:
        return createString("Multiple Choices");
    case MovedPermanently:
        return createString("Moved Permanently");
    case Found:
        return createString("Found");
    case SeeOther:
        return createString("See Other");
    case NotModified:
        return createString("Not Modified");
    case UseProxy:
        return createString("Use Proxy");
    case TemporaryRedirect:
        return createString("Temporary Redirect");
    case BadRequest:
        return createString("Bad Request");
    case Unauthorized:
        return createString("Unauthorized");
    case PaymentRequired:
        return createString("Payment Required");
    case Forbidden:
        return createString("Forbidden");
    case NotFound:
        return createString("Not Found");
    case MethodNotAllowed:
        return createString("Method Not Allowed");
    case NotAcceptable:
        return createString("Not Acceptable");
    case ProxyAuthenticationRequired:
        return createString("Proxy Authentication Required");
    case RequestTimeTou:
        return createString("Request Time-out");
    case Conflict:
        return createString("Conflict");
    case Gone:
        return createString("Gone");
    case LengthRequired:
        return createString("Length Required");
    case PreconditionFailed:
        return createString("Precondition Failed");
    case RequestEntityToLarge:
        return createString("Request Entity Too Large");
    case RequestUriTooLarge:
        return createString("Request-URI Too Large");
    case UnsupportedMediaType:
        return createString("Unsupported Media Type");
    case RequestedRangeNotSatisfiable:
        return createString("Requested range not satisfiable");
    case ExpectationFailed:
        return createString("Expectation Failed");
    case InternalServerError:
        return createString("Internal Server Error");
    case NotImplemented:
        return createString("Not Implemented");
    case BadGateway:
        return createString("Bad Gateway");
    case ServiceUnavailable:
        return createString("Service Unavailable");
    case GatewayTimeOut:
        return createString("Gateway Time-out");
    case VersionNotSupported:
        return createString("HTTP Version not supported");
    default:
        return createString("Unknown");
    }
}

} // namespace obotcha