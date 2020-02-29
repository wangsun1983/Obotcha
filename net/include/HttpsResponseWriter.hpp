#ifndef __HTTPS_RESPONSE_WRITER_HPP__
#define __HTTPS_RESPONSE_WRITER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>

extern "C" {
#include "openssl/ssl.h"
#include "openssl/err.h"
}


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "SocketListener.hpp"
#include "TcpServer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpsResponseWriter) {

};

}
#endif
