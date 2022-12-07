#include <vector>

#include "CipherDebug.hpp"

namespace obotcha {

void _CipherDebug::dumpSSLError() {
    std::vector<char> buffer;
    buffer.resize(1024);

    ERR_load_crypto_strings();
    ERR_error_string_n(ERR_get_error(), buffer.data(), buffer.size());
    printf("error reason is %s \n",buffer.data());
}

}
