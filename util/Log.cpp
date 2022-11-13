#include <initializer_list>

#include "Log.hpp"

namespace obotcha {

void InitLog() { 
    google::InitGoogleLogging("Obotcha"); 
}

void SetLogFile(String infoPrefix, String warningPrefix, String errorPrefix,
                String fatalPrefix) {
    if (infoPrefix != nullptr) {
        google::SetLogDestination(google::GLOG_INFO, infoPrefix->toChars());
    }

    if (warningPrefix != nullptr) {
        google::SetLogDestination(google::GLOG_WARNING,
                                  warningPrefix->toChars());
    }

    if (errorPrefix != nullptr) {
        google::SetLogDestination(google::GLOG_ERROR, errorPrefix->toChars());
    }

    if (fatalPrefix != nullptr) {
        google::SetLogDestination(google::GLOG_FATAL, fatalPrefix->toChars());
    }
}

void SetPrintLogLevel(int level) { 
    google::SetStderrLogging(level); 
}

void DeInitLog() { 
    google::ShutdownGoogleLogging(); 
}

} // namespace obotcha