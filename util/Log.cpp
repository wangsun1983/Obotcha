#include <initializer_list>

#include "Log.hpp"
#include "File.hpp"

namespace obotcha {

sp<_Log> _Log::mInstance = nullptr;

Log _Log::getInstance() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        _Log *log = new _Log();
        mInstance = AutoClone(log);
    });
    
    return mInstance;
}

_Log::_Log() {
    isEnable = false;
}

_Log * _Log::setTag(String tag) {
    mTag = tag;
    return this;
}

void _Log::setLogPath(int type,String path,String prefix) {
    if(isEnable == true) {
        deInit();
        isEnable = false;
    }
    File logFile = createFile(path);
    if(logFile->isDirectory() && !logFile->exists()) {
        logFile->createDirs();
    }

    if(prefix != nullptr) {
        path = logFile->getAbsolutePath()->append("/",prefix);
    } else {
        path = logFile->getAbsolutePath();
    }

    google::SetLogDestination(type, path->toChars());
}

void _Log::init() { 
    google::InitGoogleLogging("Obotcha"); 
}

_Log * _Log::setInfoLogPath(String path,String prefix) {
    setLogPath(google::GLOG_INFO,path,prefix);
    return this;
}

_Log * _Log::setWarningLogPath(String path,String prefix) {
    setLogPath(google::GLOG_WARNING,path,prefix);
    return this;
}

_Log * _Log::setErrorLogPath(String path,String prefix) {
    setLogPath(google::GLOG_ERROR,path,prefix);
    return this;
}

_Log * _Log::setFatalLogPath(String path,String prefix) {
    setLogPath(google::GLOG_FATAL,path,prefix);
    return this;
}

_Log * _Log::setPrintLogLevel(int level) { 
    google::SetStderrLogging(level); 
    return this;
}

void _Log::complete() {
    isEnable = true;
}

void _Log::deInit() { 
    google::ShutdownGoogleLogging(); 
}

void _Log::close() {
    deInit();
}

} // namespace obotcha