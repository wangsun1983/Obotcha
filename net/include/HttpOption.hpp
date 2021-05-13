#ifndef __OBOTCHA_HTTP_OPTION_HPP__
#define __OBOTCHA_HTTP_OPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpOption) IMPLEMENTS(SocketOption){
public:
    _HttpOption();
    _HttpOption* setCertificate(String);
    _HttpOption* setKey(String);
    
    String getCertificate();
    String getKey();

private:
    String mCretificate;
    String mKey;
};

}
#endif
