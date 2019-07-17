#ifndef __HTTP_URL_HPP__
#define __HTTP_URL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

#if 0
enum http_parser_url_fields
  { UF_SCHEMA           = 0  //模式，协议
  , UF_HOST             = 1  //主机名
  , UF_PORT             = 2  //端口
  , UF_PATH             = 3  //路径
  , UF_QUERY            = 4  //参数   - ?开始的部分
  , UF_FRAGMENT         = 5  //锚标志 - #开始的部分
  , UF_USERINFO         = 6  //用户名 - @之前的部分
  , UF_MAX              = 7
  };
#endif 

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpUrl) {
public:
    _HttpUrl();
    
    void setSchema(String);
    void setHost(String);
    void setPort(int);
    void setPath(String);
    void addQuery(String,String);
    void setFragment(String);
    void setUserInfo(String);

    String getSchema();
    String getHost();
    int getPort();
    String getPath();
    String getQuery(String);
    HashMap<String,String> getQuery();
    String getFragment();
    String getUserInfo();
    
private:
    String mSchema;
    String mHostName;
    int mPort;
    String mPath;
    HashMap<String,String> mQuery;
    String mFragment;
    String mUserInfo;
};
}

#endif
