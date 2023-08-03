#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_CH_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_CH_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptCh) {

public:
    _HttpHeaderAcceptCh();
    explicit _HttpHeaderAcceptCh(String);

    void load(String);
    ArrayList<String> get();
    void add(String);
    String toString() override;

private:
    ArrayList<String> accepts;
};

}
#endif
