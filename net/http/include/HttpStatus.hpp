#ifndef __OBOTCHA_HTTP_STATUS_HPP__
#define __OBOTCHA_HTTP_STATUS_HPP__

#include <mutex>

#include "Object.hpp"
#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(HttpStatus) {
public:
    
    static String toString(int);
	static int toId(String);
	static bool isValid(String);

	const static int Continue;					  // code value:100;
	const static int SwitchProtocls;			  // code value:101;
	const static int Ok;						  // code value:200;
	const static int Created;					  // code value:201;
	const static int Accepted;					  // code value:202;
	const static int NonAuthoritativeInformation; // code value:203;
	const static int NoContent;					  // code value:204;
	const static int ResetContent;				  // code value:205;
	const static int PartialContent;			  // code value:206;
	const static int MultipleChoices;			  // code value:300;
	const static int MovedPermanently;			  // code value:301;
	const static int Found;						  // code value:302;
	const static int SeeOther;					  // code value:303;
	const static int NotModified;				  // code value:304;
	const static int UseProxy;					  // code value:305;
	const static int TemporaryRedirect;			   // code value:307;
	const static int BadRequest;				   // code value:400;
	const static int Unauthorized;				   // code value:401;
	const static int PaymentRequired;			   // code value:402;
	const static int Forbidden;					   // code value:403;
	const static int NotFound;					   // code value:404;
	const static int MethodNotAllowed;			   // code value:405;
	const static int NotAcceptable;				   // code value:406;
	const static int ProxyAuthenticationRequired;  // code value:407;
	const static int RequestTimeout;			   // code value:408;
	const static int Conflict;					   // code value:409;
	const static int Gone;						   // code value:410;
	const static int LengthRequired;			   // code value:411;
	const static int PreconditionFailed;		   // code value:412;
	const static int RequestEntityToLarge;		   // code value:413;
	const static int RequestUriTooLarge;		   // code value:414;
	const static int UnsupportedMediaType;		   // code value:415;
	const static int RequestedRangeNotSatisfiable; // code value:416;
	const static int ExpectationFailed;			   // code value:417;
	const static int InternalServerError;		   // code value:500;
	const static int NotImplemented;			   // code value:501;
	const static int BadGateway;				   // code value:502;
	const static int ServiceUnavailable;		   // code value:503;
	const static int GatewayTimeout;			   // code value:504;
	const static int VersionNotSupported;		   // code value:505;

private:
	static HashMap<String,Integer> mNames;
	static HashMap<int,String> mIds;
	static void init();
	static std::once_flag s_flag;

};

}
#endif
