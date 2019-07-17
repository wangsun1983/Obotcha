#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpHeaderParser.hpp"

namespace obotcha {

String _HttpHeaderParser::HttpHeaderList[] = {
    ":Authority",
    ":Method",
    ":Path",
    ":Scheme",
    ":Status",
    ":Protocol",
    "Accept",
    "Accept-Charset",
    "Accept-Datetime",
    "Accept-Encoding",
    "Accept-Language",
    "Accept-Ranges",
    "Access-Control-Allow-Credentials",
    "Access-Control-Allow-Headers",
    "Access-Control-Allow-Methods",
    "Access-Control-Allow-Origin",
    "Access-Control-Expose-Headers",
    "Access-Control-Max-Age",
    "Access-Control-Request-Headers",
    "Access-Control-Request-Method",
    "Age",
    "Allow",
    "Alt-Svc",
    "Authorization",
    "Cache-Control",
    "Connection",
    "Content-Disposition",
    "Content-Encoding",
    "Content-Language",
    "Content-Length",
    "Content-Location",
    "Content-MD5",
    "Content-Range",
    "Content-Type",
    "Cookie",
    "DNT",
    "Date",
    "ETag",
    "Expect",
    "Expires",
    "From",
    "Front-End-Https",
    "Host",
    "If-Match",
    "If-Modified-Since",
    "If-None-Match",
    "If-Range",
    "If-Unmodified-Since",
    "Keep-Alive",
    "Last-Modified",
    "Link",
    "Location",
    "Max-Forwards",
    "Origin",
    "P3P",
    "Pragma",
    "Proxy-Authenticate",
    "Proxy-Authorization",
    "Proxy-Connection",
    "Range",
    "Referer",
    "Refresh",
    "Retry-After",
    "Sec-WebSocket-Key",
    "Sec-WebSocket-Accept",
    "Server",
    "Set-Cookie",
    "Sec-Token-Binding",
    "Strict-Transport-Security",
    "TE",
    "Timestamp",
    "Trailer",
    "Transfer-Encoding",
    "Upgrade",
    "User-Agent",
    "VIP",
    "Vary",
    "Via",
    "WWW-Authenticate",
    "Warning",
    "X-Accel-Redirect",
    "X-Content-Security-Policy-Report-Only",
    "X-Content-Type-Options",
    "X-Forwarded-For",
    "X-Forwarded-Proto",
    "X-Frame-Options",
    "X-Powered-By",
    "X-Real-IP",
    "X-Requested-With",
    "X-Thrift-Protocol",
    "X-UA-Compatible",
    "X-Wap-Profile",
    "X-XSS-Protection",
};

//wangsl

String _HttpHeaderParser::getHeaderString(int header) {
    return HttpHeaderList[header];
}

int _HttpHeaderParser::parseHttpHeader(String header) {
    const char * headcontent = header->toChars();
    int size = header->size();
    switch(headcontent[0]) {
        case ':':
        return parse_with_colon(headcontent);

        case 'A':
        case 'a':
        return parse_with_A(headcontent);

        case 'C':
        case 'c':
        return parse_with_C(headcontent);

        case 'D':
        case 'd':
        return parse_with_D(headcontent);

        case 'E':
        case 'e':
        return parse_with_E(headcontent);

        case 'F':
        case 'f':
        return parse_with_F(headcontent);

        case 'H':
        case 'h':
        return Http_Header_Host;

        case 'I':
        case 'i':
        return parse_with_I(headcontent);

        case 'K':
        case 'k':
        return Http_Header_Keep_Alive;

        case 'L':
        case 'l':
        return parse_with_L(headcontent);

        case 'M':
        case 'm':
        return Http_Header_Max_Forwards;

        case 'O':
        case 'o':
        return Http_Header_Origin;

        case 'P':
        case 'p':
        return parse_with_P(headcontent);

        case 'R':
        case 'r':
        return parse_with_R(headcontent);

        case 'S':
        case 's':
        return parse_with_S(headcontent);

        case 'T':
        case 't':
        return parse_with_T(headcontent);

        case 'U':
        case 'u':
        return parse_with_U(headcontent);

        case 'V':
        case 'v':
        return parse_with_V(headcontent);

        case 'W':
        case 'w':
        return parse_with_W(headcontent);

        case 'X':
        case 'x':
        return parse_with_X(headcontent);
    }

    return -1;
}

int _HttpHeaderParser::parse_with_colon(const char *content) {
    switch(content[1]) {
        case 'A':
        case 'a':
        return Http_Header_Authority;

        case 'M':
        case 'm':
        return Http_Header_Method;

        case 'P':
        case 'p':
        return parse_with_colon_P(content);

        case 'S':
        case 's':
        return parse_with_colon_S(content);
    }

    return  -1;
}

int _HttpHeaderParser::parse_with_colon_S(const char *content){
    switch(content[2]) {
        case 'C':
        case 'c':
        return Http_Header_Scheme;

        case 'T':
        case 't':
        return Http_Header_Status;
    }

    return  -1;
}


int _HttpHeaderParser::parse_with_colon_P(const char *content) {
    switch(content[2]) {
        case 'A':
        case 'a':
        return Http_Header_Path;

        case 'R':
        case 'r':
        return Http_Header_Protocol;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_A(const char *content) {
    switch(content[1]) {
        case 'G':
        case 'g':
        return Http_Header_Age;

        case 'U':
        case 'u':
        return Http_Header_Authorization;

        case 'C':
        case 'c':
        return parse_with_A_C(content);

        case 'L':
        case 'l':
        return parse_with_A_L(content);
    }

    return -1;
}

int _HttpHeaderParser::parse_with_A_C(const char *content) {
    switch(content[5]) {
        case 'T':
        case 't':
        return parse_with_A_C_T(content);

        case 'S':
        case 's':
        return parse_with_A_C_S(content);
    }
    return -1;
}

int _HttpHeaderParser::parse_with_A_C_T(const char *content) {
    if(content[6] == '\0') {
        return Http_Header_Accept;
    }

    switch(content[7]) {
        case 'C':
        case 'c':
        return Http_Header_Accept_Charset;

        case 'D':
        case 'd':
        return Http_Header_Accept_Datetime;

        case 'E':
        case 'e':
        return Http_Header_Accept_Encoding;

        case 'L':
        case 'l':
        return Http_Header_Accept_Language;

        case 'R':
        case 'r':
        return Http_Header_Accept_Ranges;
    }
}

int _HttpHeaderParser::parse_with_A_C_S(const char *content) {
    switch(content[15]) {
        case 'A':
        case 'a':
        return parse_witch_A_C_S_A(content);

        case 'E':
        case 'e':
        return Http_Header_Access_Control_Expose_Headers;

        case 'M':
        case 'm':
        return Http_Header_Access_Control_Max_Age;

        case 'R':
        case 'r':
        return parse_witch_A_C_S_R(content);
    }

    return  -1;
}

int _HttpHeaderParser::parse_witch_A_C_S_R(const char *content) {
    switch(content[23]) {
        case 'H':
        case 'h':
        return Http_Header_Access_Control_Request_Headers;

        case 'M':
        case 'm':
        return Http_Header_Access_Control_Request_Method;
    }
    return -1;
}

int _HttpHeaderParser::parse_witch_A_C_S_A(const char *content) {
    switch(content[21]) {
        case 'C':
        case 'c':
        return Http_Header_Access_Control_Allow_Credentials;

        case 'H':
        case 'h':
        return Http_Header_Access_Control_Allow_Headers;

        case 'M':
        case 'm':
        return Http_Header_Access_Control_Allow_Methods;

        case 'O':
        case 'o':
        return Http_Header_Access_Control_Allow_Origin;
    }

    return  -1;
}

int _HttpHeaderParser::parse_with_A_L(const char *content) {
    switch(content[2]) {
        case 'L':
        case 'l':
        return Http_Header_Allow;

        case 'T':
        case 't':
        return Http_Header_Alt_Svc;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_C(const char *content) {
    switch(content[1]) {
        case 'A':
        case 'a':
        return Http_Header_Cache_Control;

        case 'O':
        case 'o':
        return parse_with_C_O(content);
    }

    return -1;
}

int  _HttpHeaderParser::parse_with_C_O(const char *content) {
    switch(content[3]) {
        case 'K':
        case 'k':
        return Http_Header_Cookie;

        case 'N':
        case 'n':
        return Http_Header_Connection;
        
        case 'T':
        case 't':
        return parse_with_C_O_T(content);
    }
    return  -1;
}

int  _HttpHeaderParser::parse_with_C_O_T(const char *content) {
    switch(content[8]) {
        case 'D':
        case 'd':
        return Http_Header_Content_Disposition;

        case 'E':
        case 'e':
        return Http_Header_Content_Encoding;

        case 'M':
        case 'm':
        return Http_Header_Content_MD5;

        case 'R':
        case 'r':
        return Http_Header_Content_Range;

        case 'T':
        case 't':
        return Http_Header_Content_Type;

        case 'L':
        case 'l':
        return parse_with_C_O_T_L(content);
    }
    return  -1;
}

int _HttpHeaderParser::parse_with_C_O_T_L(const char *content) {
    switch(content[9]) {
        case 'A':
        case 'a':
        return Http_Header_Content_Language;

        case 'E':
        case 'e':
        return Http_Header_Content_Length;

        case 'O':
        case 'o':
        return Http_Header_Content_Location;
    }

    return  -1;
}

int _HttpHeaderParser::parse_with_D(const char *content) {
    switch(content[1]) {
        case 'N':
        case 'n':
        return Http_Header_DNT;

        case 'A':
        case 'a':
        return Http_Header_Date;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_E(const char *content) {
    switch(content[1]) {
        case 'T':
        case 't':
        return Http_Header_ETag;

        case 'X':
        case 'x':
        return parse_with_E_X(content);
    }

    return -1;
}

int _HttpHeaderParser::parse_with_E_X(const char *content) {
    switch(content[3]) {
        case 'E':
        case 'e':
        return Http_Header_Expect;

        case 'I':
        case 'i':
        return Http_Header_Expires;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_F(const char *content) {
    switch(content[3]) {
        case 'M':
        case 'm':
        return Http_Header_From;

        case 'N':
        case 'n':
        return Http_Header_Front_End_Https;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_I(const char *content) {
    switch(content[3]) {
        case 'M':
        case 'm':
        return parse_with_I_M(content);

        case 'N':
        case 'n':
        return Http_Header_If_None_Match;

        case 'R':
        case 'r':
        return Http_Header_If_Range;

        case 'U':
        case 'u':
        return Http_Header_If_Unmodified_Since;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_I_M(const char *content) {
    switch(content[4]) {
        case 'A':
        case 'a':
        return Http_Header_If_Match;

        case 'O':
        case 'o':
        return Http_Header_If_Modified_Since;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_L(const char *content) {
    switch(content[1]) {
        case 'A':
        case 'a':
        return Http_Header_Last_Modified;

        case 'I':
        case 'i':
        return Http_Header_Link;

        case 'O':
        case 'o':
        return Http_Header_Location;
    }
    return -1;
}

int _HttpHeaderParser::parse_with_P(const char *content) {
    switch(content[1]) {
        case '3':
        return Http_Header_P3P;

        case 'R':
        case 'r':
        return parse_with_P_R(content);
    }

    return  -1;
}

int _HttpHeaderParser::parse_with_P_R(const char *content) {
    switch(content[2]) {
        case 'A':
        case 'a':
        return Http_Header_Pragma;

        case 'O':
        case 'o':
        return parse_with_P_R_O(content);
    }
    return -1;
}

int _HttpHeaderParser::parse_with_P_R_O(const char *content) {
    switch(content[6]) {
        case 'A':
        case 'a':
        return parse_with_P_R_O_A(content);

        case 'C':
        case 'c':
        return Http_Header_Proxy_Connection;
    }
    return -1;
}

int _HttpHeaderParser::parse_with_P_R_O_A(const char *content) {
    switch(content[10]) {
        case 'E':
        case 'e':
        return Http_Header_Proxy_Authenticate;

        case 'O':
        case 'o':
        return Http_Header_Proxy_Authorization;
    }
    return -1;
}

int _HttpHeaderParser::parse_with_R(const char *content) {
    switch(content[1]) {
        case 'A':
        case 'a':
        return Http_Header_Range;

        case 'E':
        case 'e':
        return parse_with_R_E(content);
    }
    return -1;
}

int _HttpHeaderParser::parse_with_R_E(const char *content) {
    switch(content[4]) {
        case 'R':
        case 'r':
        return Http_Header_Referer;

        case 'E':
        case 'e':
        return Http_Header_Refresh;

        case 'Y':
        case 'y':
        return Http_Header_Retry_After;
    }
    return -1;
}

int _HttpHeaderParser::parse_with_S(const char *content) {
    switch(content[1]) {
        case 'T':
        case 't':
        return Http_Header_Strict_Transport_Security;

        case 'E':
        case 'e':
        return parse_with_S_E(content);
    }

    return -1;
}

int _HttpHeaderParser::parse_with_S_E(const char *content) {
    switch(content[2]) {
        case 'C':
        case 'c':
        return parse_with_S_E_C(content);

        case 'R':
        case 'r':
        return Http_Header_Server;

        case 'T':
        case 't':
        return Http_Header_Set_Cookie;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_S_E_C(const char *content) {
    switch(content[4]) {
        case 'W':
        case 'w':
        return parse_with_S_E_C_W(content);

        case 'T':
        case 't':
        return Http_Header_Sec_Token_Binding;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_S_E_C_W(const char *content) {
    switch(content[14]) {
        case 'K':
        case 'k':
        return Http_Header_Sec_WebSocket_Key;

        case 'A':
        case 'a':
        return Http_Header_Sec_WebSocket_Accept;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_T(const char *content) {
    switch(content[1]) {
        case 'E':
        case 'e':
        return Http_Header_TE;

        case 'I':
        case 'i':
        return Http_Header_Timestamp;

        case 'R':
        case 'r':
        return parse_with_T_R(content);
    }

    return -1;
}

int _HttpHeaderParser::parse_with_T_R(const char *content) {
    switch(content[3]) {
        case 'I':
        case 'i':
        return Http_Header_Trailer;

        case 'N':
        case 'n':
        return Http_Header_Transfer_Encoding;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_U(const char *content) {
    switch(content[1]) {
        case 'P':
        case 'p':
        return Http_Header_Upgrade;

        case 'S':
        case 's':
        return Http_Header_User_Agent;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_V(const char *content) {
    switch(content[2]) {
        case 'P':
        case 'p':
        return Http_Header_VIP;

        case 'R':
        case 'r':
        return Http_Header_Vary;

        case 'A':
        case 'a':
        return Http_Header_Via;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_W(const char *content) {
    switch(content[1]) {
        case 'W':
        case 'w':
        return Http_Header_WWW_Authenticate;

        case 'A':
        case 'a':
        return Http_Header_Warning;
    }

    return -1;
}


int _HttpHeaderParser::parse_with_X(const char *content) {
    switch(content[2]) {
        case 'A':
        case 'a':
        return Http_Header_X_Accel_Redirect;

        case 'C':
        case 'c':
        return parse_with_X_C(content);

        case 'F':
        case 'f':
        return parse_with_X_F(content);

        case 'P':
        case 'p':
        return Http_Header_X_Powered_By;

        case 'R':
        case 'r':
        return parse_with_X_R(content);

        case 'T':
        case 't':
        return Http_Header_X_Thrift_Protocol;

        case 'U':
        case 'u':
        return Http_Header_X_UA_Compatible;

        case 'W':
        case 'w':
        return Http_Header_X_Wap_Profile;

        case 'X':
        case 'x':
        return Http_Header_X_XSS_Protection;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_X_C(const char *content) {
    switch(content[10]) {
        case 'S':
        case 's':
        return Http_Header_X_Content_Security_Policy_Report_Only;

        case 'T':
        case 't':
        return Http_Header_X_Content_Type_Options;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_X_F(const char *content) {
    switch(content[12]) {
        case 'F':
        case 'f':
        return Http_Header_X_Forwarded_For;

        case 'P':
        case 'p':
        return Http_Header_X_Forwarded_Proto;

        case 'O':
        case 'o':
        return Http_Header_X_Frame_Options;
    }

    return -1;
}

int _HttpHeaderParser::parse_with_X_R(const char *content) {
    switch(content[4]) {
        case 'A':
        case 'a':
        return Http_Header_X_Real_IP;

        case 'Q':
        case 'q':
        return Http_Header_X_Requested_With;
    }

    return -1;
}






































}

