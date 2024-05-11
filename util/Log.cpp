#include <initializer_list>

#include "Log.hpp"
#include "File.hpp"

namespace obotcha {

sp<_Log> _Log::mInstance = nullptr;

Log _Log::getInstance() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        auto log = new _Log();
        log->init();
        mInstance = AutoClone(log);
    });
    
    return mInstance;
}

_Log::_Log() {
    FLAGS_alsologtostderr = true;
}

_Log * _Log::setTag(String tag) {
    mTag = tag;
    return this;
}

void _Log::setLogPath(int type,String path,String prefix) const {
    File logFile = File::New(path);
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
    isEnable = true;
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

_Log * _Log::setPrintLogLevel(Level l) { 
    google::SetStderrLogging(static_cast<int>(l)); 
    return this;
}

_Log * _Log::startSetting() {
    if(isEnable) {
        deInit();
    }
    isEnable = false;
    return this;
}

void _Log::completeSetting() {
    init();
}

void _Log::deInit() const { 
    google::ShutdownGoogleLogging(); 
}

void _Log::close() {
    deInit();
}

} // namespace obotcha