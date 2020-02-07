#ifndef __HTTP_V1_RESPONSE_WRITER_HPP__
#define __HTTP_V1_RESPONSE_WRITER_HPP__

#include "HttpPacket.hpp"
#include "HttpV1ClientInfo.hpp"

namespace obotcha {

enum HttpV1ResponseStatus {

};

DECLARE_SIMPLE_CLASS(HttpV1ResponseWriter) {
public:
    _HttpV1ResponseWriter(HttpV1ClientInfo client);
    
    void writeHeader(String,String);

    void writeBody(ByteArray);

    void setStatus(int);

	int write(HttpPacket);

    int write(File);
    
    int flush();

private:
    int mFd;

    HttpPacket mPacket;

    HttpV1ClientInfo mClient;

    File mFile;
};

}

#endif
