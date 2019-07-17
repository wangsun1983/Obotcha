#ifndef __HTTP_HEADER_PARSER_HPP__
#define __HTTP_HEADER_PARSER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

namespace obotcha {

enum HTTP_HEADER {
    Http_Header_Authority = 0,
    Http_Header_Method,
    Http_Header_Path,
    Http_Header_Scheme,
    Http_Header_Status,
    Http_Header_Protocol,
    Http_Header_Accept,
    Http_Header_Accept_Charset,
    Http_Header_Accept_Datetime,
    Http_Header_Accept_Encoding,
    Http_Header_Accept_Language,
    Http_Header_Accept_Ranges,
    Http_Header_Access_Control_Allow_Credentials,
    Http_Header_Access_Control_Allow_Headers,
    Http_Header_Access_Control_Allow_Methods,
    Http_Header_Access_Control_Allow_Origin,
    Http_Header_Access_Control_Expose_Headers,
    Http_Header_Access_Control_Max_Age,
    Http_Header_Access_Control_Request_Headers,
    Http_Header_Access_Control_Request_Method,
    Http_Header_Age,
    Http_Header_Allow,
    Http_Header_Alt_Svc,
    Http_Header_Authorization,
    Http_Header_Cache_Control,
    Http_Header_Connection,
    Http_Header_Content_Disposition,
    Http_Header_Content_Encoding,
    Http_Header_Content_Language,
    Http_Header_Content_Length,
    Http_Header_Content_Location,
    Http_Header_Content_MD5,
    Http_Header_Content_Range,
    Http_Header_Content_Type,
    Http_Header_Cookie,
    Http_Header_DNT,
    Http_Header_Date,
    Http_Header_ETag,
    Http_Header_Expect,
    Http_Header_Expires,
    Http_Header_From,
    Http_Header_Front_End_Https,
    Http_Header_Host,
    Http_Header_If_Match,
    Http_Header_If_Modified_Since,
    Http_Header_If_None_Match,
    Http_Header_If_Range,
    Http_Header_If_Unmodified_Since,
    Http_Header_Keep_Alive,
    Http_Header_Last_Modified,
    Http_Header_Link,
    Http_Header_Location,
    Http_Header_Max_Forwards,
    Http_Header_Origin,
    Http_Header_P3P,
    Http_Header_Pragma,
    Http_Header_Proxy_Authenticate,
    Http_Header_Proxy_Authorization,
    Http_Header_Proxy_Connection,
    Http_Header_Range,
    Http_Header_Referer,
    Http_Header_Refresh,
    Http_Header_Retry_After,
    Http_Header_Sec_WebSocket_Key,
    Http_Header_Sec_WebSocket_Accept,
    Http_Header_Server,
    Http_Header_Set_Cookie,
    Http_Header_Sec_Token_Binding,
    Http_Header_Strict_Transport_Security,
    Http_Header_TE,
    Http_Header_Timestamp,
    Http_Header_Trailer,
    Http_Header_Transfer_Encoding,
    Http_Header_Upgrade,
    Http_Header_User_Agent,
    Http_Header_VIP,
    Http_Header_Vary,
    Http_Header_Via,
    Http_Header_WWW_Authenticate,
    Http_Header_Warning,
    Http_Header_X_Accel_Redirect,
    Http_Header_X_Content_Security_Policy_Report_Only,
    Http_Header_X_Content_Type_Options,
    Http_Header_X_Forwarded_For,
    Http_Header_X_Forwarded_Proto,
    Http_Header_X_Frame_Options,
    Http_Header_X_Powered_By,
    Http_Header_X_Real_IP,
    Http_Header_X_Requested_With,
    Http_Header_X_Thrift_Protocol,
    Http_Header_X_UA_Compatible,
    Http_Header_X_Wap_Profile,
    Http_Header_X_XSS_Protection,
    Http_Header_Max,
};

DECLARE_SIMPLE_CLASS(HttpHeaderParser) {

public:
    static String getHeaderString(int header);
    static int parseHttpHeader(String header);

private:
    static String HttpHeaderList[];
    static HashMap<String,int> HttpHeaderMap;

    static int parse_with_colon(const char *);
    static int parse_with_colon_P(const char *);
    static int parse_with_colon_S(const char *);

    static int parse_with_A(const char *);
    static int parse_with_A_L(const char *);
    static int parse_with_A_C(const char *);
    static int parse_with_A_C_T(const char *);
    static int parse_with_A_C_S(const char *);
    static int parse_witch_A_C_S_R(const char *);
    static int parse_witch_A_C_S_A(const char *);

    static int parse_with_C(const char *);
    static int parse_with_C_O(const char *);
    static int parse_with_C_O_T(const char *);
    static int parse_with_C_O_T_L(const char *);

    static int parse_with_D(const char *);

    static int parse_with_E(const char *);
    static int parse_with_E_X(const char *);

    static int parse_with_F(const char *);

    static int parse_with_I(const char *);
    static int parse_with_I_M(const char *);
    
    static int parse_with_L(const char *);
    
    static int parse_with_P(const char *);
    static int parse_with_P_R(const char *);
    static int parse_with_P_R_O(const char *);
    static int parse_with_P_R_O_A(const char *);

    static int parse_with_R(const char *);
    static int parse_with_R_E(const char *);

    static int parse_with_S(const char *);
    static int parse_with_S_E(const char *);
    static int parse_with_S_E_C(const char *);
    static int parse_with_S_E_C_W(const char *);

    static int parse_with_T(const char *);
    static int parse_with_T_R(const char *);

    static int parse_with_U(const char *);
    static int parse_with_V(const char *);
    static int parse_with_W(const char *);
    static int parse_with_X(const char *);
    static int parse_with_X_R(const char *);
    static int parse_with_X_F(const char *);
    static int parse_with_X_C(const char *);
};
}

#endif
