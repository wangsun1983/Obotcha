#ifndef __OBOTCHA_HTTP_OPTION_HPP__
#define __OBOTCHA_HTTP_OPTION_HPP__

#include "Object.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_CLASS(HttpOption) IMPLEMENTS(SocketOption) {
public:
    _HttpOption();
    _HttpOption *setProtocol(int);
    int getProtocol();

private:
    int mProtocol;
};

} // namespace obotcha
#endif
