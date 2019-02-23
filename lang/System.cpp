#include "System.hpp"
#include <sys/time.h>
#include <unistd.h>

long int _System::currentTimeMillis() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000 + tv.tv_usec/1000;
}

int _System::availableProcessors() {
    int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    return cpu_num;
}

int _System::onlineProcessors(){
    int cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
    return cpu_num;
}

void _System::exit(int reason) {
    exit(reason);
}