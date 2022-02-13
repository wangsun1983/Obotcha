#ifndef __OBOTCHA_HTTP_OPTION_HPP__
#define __OBOTCHA_HTTP_OPTION_HPP__

#include <fstream>
#include <mqueue.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "InetAddress.hpp"
#include "SocketOption.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpOption) IMPLEMENTS(SocketOption) {
  public:
    _HttpOption();
    _HttpOption *setOpenSSLCertificate(String);
    _HttpOption *setOpenSSLKey(String);
    _HttpOption *setProtocol(int);

    String getOpenSSLCertificate();
    String getOpenSSLKey();
    int getProtocol();

  private:
    String mCretificate;
    String mKey;
    int mProtocol;
};

} // namespace obotcha
#endif
