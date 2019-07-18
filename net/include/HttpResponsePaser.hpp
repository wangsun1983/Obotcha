#ifndef __HTTP_RESPONSE_STATUS_HPP__
#define __HTTP_RESPONSE_STATUS_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

namespace obotcha {

enum HTTP_HEADER {
    
};

DECLARE_SIMPLE_CLASS(HttpResponseStatus) {

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
