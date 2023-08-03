#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_USER_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_USER_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchUser) {

public:
    _HttpHeaderSecFetchUser() = default;
    explicit _HttpHeaderSecFetchUser(String);

    void load(String);

    void set(String);

    String get();

    String toString() override;

    const static String kUserActivate;
    const static String kOtherActivate;

private:
    String value;
};

}
#endif
