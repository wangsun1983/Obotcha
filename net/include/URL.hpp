#ifndef __OBOTCHA_URL_HPP__
#define __OBOTCHA_URL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(URL) {
public:
    _URL(String);

    ArrayList<InetAddress> getInetAddress();

private:
    String uri;
};

}

#endif