#include "System.hpp"
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

namespace obotcha {

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

String _System::executeForResult(String cmd) {
    FILE * fp;
    char buffer[1024*4];
    fp = popen(cmd->toChars(),"r");
    
    if(fp == nullptr) {
        //printf("popen fail: %s  \n",strerror(errno));
        return nullptr;
    }

    fread(buffer,1,1024*4,fp);
    pclose(fp);

    return createString(buffer);
}

void _System::execute(String cmd) {
    system(cmd->toChars());
}

void _System::exit(int reason) {
    exit(reason);
}

}