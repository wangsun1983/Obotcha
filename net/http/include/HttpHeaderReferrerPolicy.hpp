#ifndef __OBOTCHA_HTTP_HEADER_REFERRER_POLICY_HPP__
#define __OBOTCHA_HTTP_HEADER_REFERRER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderReferrerPolicy) {

public:
    _HttpHeaderReferrerPolicy() = default;
    explicit _HttpHeaderReferrerPolicy(String);

    void load(String);
    
    ArrayList<String> get();
    void set(ArrayList<String>);
    void add(String);

    String toString() override;

private:
    ArrayList<String> policies = createArrayList<String>();
};

}
#endif
