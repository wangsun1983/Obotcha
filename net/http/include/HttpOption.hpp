#ifndef __OBOTCHA_HTTP_OPTION_HPP__
#define __OBOTCHA_HTTP_OPTION_HPP__

#include "Object.hpp"
#include "SocketOption.hpp"
#include "Http.hpp"

namespace obotcha {

DECLARE_CLASS(HttpOption) IMPLEMENTS(SocketOption) {
public:
    _HttpOption();
    _HttpOption *setProtocol(st(Net)::Protocol protocol);
    st(Net)::Protocol getProtocol() const;

private:
     st(Net)::Protocol mProtocol;
};

} // namespace obotcha
#endif
