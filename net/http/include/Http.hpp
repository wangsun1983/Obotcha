#ifndef __OBOTCHA_HTTP_HPP__
#define __OBOTCHA_HTTP_HPP__

#include "Object.hpp"
#include "Net.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Http) {

public:
    enum class PacketType {
        Unknown = -1,
        Request = 0,
        Response
    };

    class Config {
        public:
            static String kMultiPartDirectory;
            static int kServerThreadNum;
            static int kBufferSize;
    };
};

}

#endif
