#ifndef __OBOTCHA_OBOTCHA_LOG_HPP__
#define __OBOTCHA_OBOTCHA_LOG_HPP__

#include <mutex>

#include "utilities.h"
#include "logging.h"

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Log) {

public:
    enum class Level {
        Info = google::GLOG_INFO,
        Warn = google::GLOG_WARNING,
        Error = google::GLOG_ERROR,
        Fatal = google::GLOG_FATAL
    };

    _Log * startSetting();
    _Log * setInfoLogPath(String path,String prefix = nullptr);
    _Log * setWarningLogPath(String path,String prefix = nullptr);
    _Log * setErrorLogPath(String path,String prefix = nullptr);
    _Log * setFatalLogPath(String path,String prefix = nullptr);
    _Log * setTag(String tag);
    _Log * setPrintLogLevel(Level);
    void completeSetting();

    static sp<_Log> getInstance();

    
    void close();
private:
    static sp<_Log> mInstance;
    _Log();
    void setLogPath(int type,String path,String prefix) const;
    void init();
    void deInit() const;
    bool isEnable = false;
    String mTag;
};

}
#endif