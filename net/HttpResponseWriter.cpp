#include "HttpResponseWriter.hpp"

namespace obotcha {

_HttpResponseWriter::_HttpResponseWriter(int fd) {
    mFd = fd;
}

int _HttpResponseWriter::write(HttpResponse) {
    //TODO
}



}
