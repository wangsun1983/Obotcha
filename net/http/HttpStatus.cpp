#include "HttpStatus.hpp"

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
//UnUsed status:306,do not define
const int _HttpStatus::TemporaryRedirect = 307;
const int _HttpStatus::BadRequest = 400;
const int _HttpStatus::Unauthorized = 401;
const int _HttpStatus::PaymentRequired = 402;
const int _HttpStatus::Forbidden = 403;
const int _HttpStatus::NotFound = 404;
const int _HttpStatus::MethodNotAllowed = 405;
const int _HttpStatus::NotAcceptable = 406;
const int _HttpStatus::ProxyAuthenticationRequired = 407;
const int _HttpStatus::RequestTimeout = 408;
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
const int _HttpStatus::GatewayTimeout = 504;
const int _HttpStatus::VersionNotSupported = 505;

HashMap<String,Integer> _HttpStatus::mNames = nullptr;
HashMap<int,String> _HttpStatus::mIds = nullptr;
std::once_flag _HttpStatus::s_flag;

String _HttpStatus::toString(int status) {
    init();
    return mIds->get(status);
}

int _HttpStatus::toId(String status) {
    init();
    status = status->trim()->toUpperCase();
    auto id = mNames->get(status);
    return (id == nullptr)?-1:id->toValue();
}

bool _HttpStatus::isValid(String status) {
    return toId(status) != -1;
}

void _HttpStatus::init() {
    std::call_once(s_flag, []() {
        mNames = HashMap<String,Integer>::New();
        mIds = HashMap<int,String>::New();
        String c = nullptr;
        String up = nullptr;

#define InitStatus(ID,STR) { \
    c = String::New(STR);\
    up = c->toUpperCase();\
    mNames->put(up,Integer::New(ID));\
    mIds->put(ID,c);\
}
        InitStatus(Continue,"Continue")
        InitStatus(SwitchProtocls,"Switching Protocols")
        InitStatus(Ok,"OK")
        InitStatus(Created,"Created")
        InitStatus(Accepted,"Accepted")
        InitStatus(NonAuthoritativeInformation,"Non-Authoritative Information")
        InitStatus(NoContent,"No Content")
        InitStatus(ResetContent,"Reset Content")
        InitStatus(PartialContent,"Partial Content")
        InitStatus(MultipleChoices,"Multiple Choices")
        InitStatus(MovedPermanently,"Moved Permanently")
        InitStatus(Found,"Found")
        InitStatus(SeeOther,"See Other")
        InitStatus(NotModified,"Not Modified")
        InitStatus(UseProxy,"Use Proxy")
        InitStatus(TemporaryRedirect,"Temporary Redirect")
        InitStatus(BadRequest,"Bad Request")
        InitStatus(Unauthorized,"Unauthorized")
        InitStatus(PaymentRequired,"Payment Required")
        InitStatus(Forbidden,"Forbidden")
        InitStatus(NotFound,"Not Found")
        InitStatus(MethodNotAllowed,"Method Not Allowed")
        InitStatus(NotAcceptable,"Not Acceptable")
        InitStatus(ProxyAuthenticationRequired,"Proxy Authentication Required")
        InitStatus(RequestTimeout,"Request Time-out")
        InitStatus(Conflict,"Conflict")
        InitStatus(Gone,"Gone")
        InitStatus(LengthRequired,"Length Required")
        InitStatus(PreconditionFailed,"Precondition Failed")
        InitStatus(RequestEntityToLarge,"Request Entity Too Large")
        InitStatus(RequestUriTooLarge,"Request-URI Too Large")
        InitStatus(UnsupportedMediaType,"Unsupported Media Type")
        InitStatus(RequestedRangeNotSatisfiable,"Requested range not satisfiable")
        InitStatus(ExpectationFailed,"Expectation Failed")
        InitStatus(InternalServerError,"Internal Server Error")
        InitStatus(NotImplemented,"Not Implemented")
        InitStatus(BadGateway,"Bad Gateway")
        InitStatus(ServiceUnavailable,"Service Unavailable")
        InitStatus(GatewayTimeout,"Gateway Time-out")
        InitStatus(VersionNotSupported,"HTTP Version not supported")
        InitStatus(-1,"Unknown")
    });
}

} // namespace obotcha