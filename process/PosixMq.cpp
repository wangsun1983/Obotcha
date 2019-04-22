#include "PosixMq.hpp"

namespace obotcha {
    
_PosixMq::_PosixMq(String name,int type) {
    String sp = "/";
    mQName = sp->append(name);
    mType = type;
}

bool _PosixMq::init() {
    mQid = mq_open(mQName->toChars(), O_RDWR | O_CREAT | O_EXCL, 0666, NULL);

    return (mQid > 0);
}

bool _PosixMq::send(ByteArray data,int prio) {
    if(mType == RecvMq) {
        return false;
    }

    int result = mq_send(mQid, data->toValue(), data->size(), prio);

    return (result != -1);
}

bool _PosixMq::send(ByteArray data) {
    return send(data);
}

int _PosixMq::receive(ByteArray buff) {
    if(mType == SendMq) {
        return false;
    }

    unsigned int prio;
    int result = mq_receive(mQid, buff->toValue(),buff->size(), &prio);

    return result;

}

_PosixMq::~_PosixMq() {
    mq_unlink(mQName->toChars());
    mq_close(mQid);
}

}
