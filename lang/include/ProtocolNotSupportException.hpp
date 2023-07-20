#ifndef __OBOTCHA_PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__
#define __OBOTCHA_PROTOCOL_NOT_SUPPORT_EXCEPTION_HPP__

#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ProtocolNotSupportException) {
public:
	ProtocolNotSupportException() = default;
};

}

#endif
