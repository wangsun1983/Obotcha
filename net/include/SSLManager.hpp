#ifndef __SSL_MANAGER_HPP__
#define __SSL_MANAGER_HPP__

#include "SSLInfo.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SSLManager) {
public:
    static SSLManager getInstance();

    void add(int,SSLInfo);

    SSLInfo get(int);

    void remove(int);

private:
    _SSLManager();

    //static SSLManager mInstance;
   
    Mutex mMutex;

    HashMap<int,SSLInfo> mSSLMap;
};

}
#endif
