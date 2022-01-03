#include "HttpResourceManager.hpp"
#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"

namespace obotcha {

std::once_flag _HttpResourceManager::s_flag;
sp<_HttpResourceManager> _HttpResourceManager::mInstance;

HttpResourceManager _HttpResourceManager::getInstance() {
    std::call_once(s_flag, [&]() {
        _HttpResourceManager *p = new _HttpResourceManager();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

_HttpResourceManager::_HttpResourceManager() {
    mResourceDir = createString("./");
    mRedirectMaps = createHashMap<String, String>();
    resourceCaches = createHashMap<String, File>();
    mReadWriteLock = createReadWriteLock();
    mWriteLock = mReadWriteLock->getWriteLock();
    mReadLock = mReadWriteLock->getReadLock();
}

void _HttpResourceManager::setResourceDir(String dir) { mResourceDir = dir; }

void _HttpResourceManager::setViewRedirect(String segment, String filename) {
    mRedirectMaps->put(segment, filename);
}

File _HttpResourceManager::findResource(String path) {
    {
        AutoLock l(mReadLock);
        File file = resourceCaches->get(path);
        if (file != nullptr) {
            return file;
        }
    }

    // we check file
    int index = path->lastIndexOf("/");
    String lastPath = nullptr;
    String checkFilePath = nullptr;
    if (index == -1) {
        lastPath = mRedirectMaps->get(path);
    } else {
        String tempPath = path->subString(index + 1, path->size() - index - 1);
        lastPath = mRedirectMaps->get(tempPath);
    }

    if (lastPath != nullptr) {
        if (lastPath->indexOf(".") == -1) {
            return nullptr;
        }

        checkFilePath = path->subString(0, index + 1);
        checkFilePath = checkFilePath->append(lastPath);
        checkFilePath = mResourceDir->append("/")->append(checkFilePath);
    } else {
        if (path->indexOf(".") == -1) {
            return nullptr;
        }
        checkFilePath = mResourceDir->append("/")->append(path);
    }

    File file = createFile(checkFilePath);

    if (file->exists()) {
        AutoLock l(mWriteLock);
        resourceCaches->put(path, file);
        return file;
    }

    return nullptr;
}

} // namespace obotcha