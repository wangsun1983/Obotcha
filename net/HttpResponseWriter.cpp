#include "HttpResponseWriter.hpp"

namespace obotcha {

_HttpResponseWriter::_HttpResponseWriter(int fd) {
    mFd = fd;
}

int _HttpResponseWriter::write(HttpPacket) {
    //TODO
    return 0;
}



}
