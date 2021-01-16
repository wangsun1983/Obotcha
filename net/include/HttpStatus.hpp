#ifndef __OBOTCHA_HTTP_STATUS_HPP__
#define __OBOTCHA_HTTP_STATUS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpStatus) {
public:
    
    static String toString(int);
	
    const static int Continue; //100;
 	const static int SwitchProtocls; //101;
 	const static int Ok; //200;
 	const static int Created; //201;
 	const static int Accepted; //202;
 	const static int NonAuthoritativeInformation; //203;
 	const static int NoContent; //204;
 	const static int ResetContent; //205;
 	const static int PartialContent; //206;
 	const static int MultipleChoices; //300;
 	const static int MovedPermanently; //301;
 	const static int Found; //302;
 	const static int SeeOther; //303;
 	const static int NotModified; //304;
 	const static int UseProxy; //305;
	//const static int UnUsed; //306;
 	const static int TemporaryRedirect; //307;
 	const static int BadRequest; //400;
 	const static int Unauthorized; //401;
 	const static int PaymentRequired; //402;
 	const static int Forbidden; //403;
 	const static int NotFound; //404;
 	const static int MethodNotAllowed; //405;
 	const static int NotAcceptable; //406;
 	const static int ProxyAuthenticationRequired; //407;
 	const static int RequestTimeTou; //408;
 	const static int Conflict; //409;
 	const static int Gone; //410;
 	const static int LengthRequired; //411;
 	const static int PreconditionFailed; //412;
 	const static int RequestEntityToLarge; //413;
 	const static int RequestUriTooLarge; //414;
 	const static int UnsupportedMediaType; //415;
 	const static int RequestedRangeNotSatisfiable; //416;
 	const static int ExpectationFailed; //417;
 	const static int InternalServerError; //500;
 	const static int NotImplemented; //501;
    const static int BadGateway; //502;
 	const static int ServiceUnavailable; //503;
 	const static int GatewayTimeOut; //504;
 	const static int VersionNotSupported; //505;

};

}
#endif
