#ifndef __WEB_SOCKET_HYBI08_COMPOSER_HPP__
#define __WEB_SOCKET_HYBI08_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 08
/**
 * The primary difference between 08 and 13 is a different origin header name
 */
DECLARE_SIMPLE_CLASS(WebSocketHybi08Composer) IMPLEMENTS(WebSocketHybi13Composer){

};

}
#endif
