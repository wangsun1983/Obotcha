#include "Lock.hpp"
#include "Error.hpp"

namespace obotcha {

int _Lock::convertResult(int ret) {
    switch(ret) {
        case EINVAL:
            return -UnLockInvalid;

        case EFAULT:
            return -UnLockFail;

        case EPERM:
            return -UnLockPerm;

        case ETIMEDOUT:
            return -WaitTimeout;

        case EBUSY:
            return -LockBusy;

        case 0:
            return SUCCESS;

        default:
            return -LockFail;
    }
}

} // namespace obotcha
