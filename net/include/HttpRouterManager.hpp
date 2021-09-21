#ifndef __OBOTCHA_HTTP_ROUTER_MANAGER_HPP__
#define __OBOTCHA_HTTP_ROUTER_MANAGER_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HashMap.hpp"
#include "HttpMethod.hpp"
#include "HttpRouterMap.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpRouterManager) {
  public:
    static sp<_HttpRouterManager> getInstance();
    void addRouter(int method, HttpRouter);
    HttpRouter getRouter(int method, String, HashMap<String, String> &);

  private:
    _HttpRouterManager();
    static std::once_flag s_flag;
    static sp<_HttpRouterManager> mInstance;

    HttpRouterMap mMaps[st(HttpMethod)::Max];
};

} // namespace obotcha

#endif
