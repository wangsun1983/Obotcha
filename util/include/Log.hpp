#ifndef __OBOTCHA_OBOTCHA_LOG_HPP__
#define __OBOTCHA_OBOTCHA_LOG_HPP__

#include <initializer_list>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "utilities.h"
#include "logging.h"
#include "String.hpp"

using namespace std;

namespace obotcha {

//GLOG_INFO = 0, GLOG_WARNING = 1, GLOG_ERROR = 2, GLOG_FATAL = 3,

enum LogLevel {
    InfoLevel = google::GLOG_INFO,
    WarnLevel = google::GLOG_WARNING,
    ErrorLevel = google::GLOG_ERROR,
    FatalLevel = google::GLOG_FATAL
};

void InitLog();
void SetLogFile(String,String,String,String);
void SetPrintLogLevel(LogLevel);
void DeInitLog();

}
#endif