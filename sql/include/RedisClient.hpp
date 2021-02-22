#ifndef __OBOTCHA_REDIS_CLIENT_H__
#define __OBOTCHA_REDIS_CLIENT_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "hiredis.h"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(RedisClient) {

public:
    int connect(String server,int port,long millseconds);
    int set(String,String);
    int set(String,int);
    
    String getValue(String);
    int incValue(String);
    int decValue(String);

    int delList(String);
    
    int set(String,ArrayList<String>);

private:
    redisContext *mContext;
    String mServer;
    int mPort;
};

} // namespace obotcha
#endif