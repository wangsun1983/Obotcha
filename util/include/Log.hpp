#ifndef __OBOTCHA_OBOTCHA_LOG_HPP__
#define __OBOTCHA_OBOTCHA_LOG_HPP__

#include <initializer_list>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "utilities.h"
#include "logging.h"
#include "String.hpp"

namespace obotcha {

//GLOG_INFO = 0, GLOG_WARNING = 1, GLOG_ERROR = 2, GLOG_FATAL = 3,

//enum LogLevel {
//    Info = google::GLOG_INFO,
//    Warn = google::GLOG_WARNING,
//    Error = google::GLOG_ERROR,
//    Fatal = google::GLOG_FATAL
//};

void InitLog();
void SetLogFile(String,String,String,String);
void SetPrintLogLevel(int);
void DeInitLog();

}
#endif