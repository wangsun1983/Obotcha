#ifndef __OBOTCHA_HTTP_RESOURCE_MANAGER_HPP__
#define __OBOTCHA_HTTP_RESOURCE_MANAGER_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "File.hpp"
#include "HashMap.hpp"
#include "ReadWriteLock.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpResourceManager) {
  public:
    static sp<_HttpResourceManager> getInstance();
    void setResourceDir(String dir);

    File findResource(String url);
    void setViewRedirect(String segment, String filename);

  private:
    _HttpResourceManager();
    static std::once_flag s_flag;
    static sp<_HttpResourceManager> mInstance;

    HashMap<String, String> mRedirectMaps;

    String mResourceDir;
    HashMap<String, File> resourceCaches;

    ReadLock mReadLock;
    WriteLock mWriteLock;
    ReadWriteLock mReadWriteLock;
};

} // namespace obotcha

#endif
