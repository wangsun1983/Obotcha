#include "DatagramSocketImpl.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(DatagramSocketImpl) IMPLEMENTS(SocketImpl){
public:
    int connect(InetAddress host, int port,SocketOption option = nullptr);
    
};

}

#endif