#include "Http2Protocol.hpp"

namespace obotcha {

const String _Http2Protocol::ConnectionPreface = createString("PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n");


}

