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
    _HttpOption *setCertificate(String);
    _HttpOption *setKey(String);

    String getCertificate();
    String getKey();

  private:
    String mCretificate;
    String mKey;
};

} // namespace obotcha
#endif
