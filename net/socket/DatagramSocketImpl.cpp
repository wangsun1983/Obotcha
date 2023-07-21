#include "DatagramSocketImpl.hpp"
#include "FileDescriptor.hpp"
#include "InitializeException.hpp"
#include "Socket.hpp"
#include "Inspect.hpp"
#include "SocketBuilder.hpp"
#include "IllegalArgumentException.hpp"
#include "Log.hpp"

namespace obotcha {

_DatagramSocketImpl::_DatagramSocketImpl():_SocketImpl(){
}

_DatagramSocketImpl::_DatagramSocketImpl(FileDescriptor fd,InetAddress address,SocketOption option) 
    :_SocketImpl(address, option){
    mSock = fd;
}

_DatagramSocketImpl::_DatagramSocketImpl(InetAddress address,
                                         SocketOption option)
    : _SocketImpl(address, option) {
    mSock = createFileDescriptor(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_DGRAM,
                                IPPROTO_UDP)));
    
    if (mSock->getFd() < 0) {
        LOG(ERROR)<<"DatagramSocket open fd failed,reason is "<<strerror(errno);
        Trigger(InitializeException, "Datagram Socket create failed");
    }

    if(option != nullptr) {
        option->update(mSock);
    }
}

Socket _DatagramSocketImpl::recvDatagram(ByteArray buff) {
    SockAddress client = createSockAddress(mAddress->getFamily());
    FetchRet(client_len,client_addr) = client->get();
    //TODO? 
    //shall we reset buff size before receive data
    int length = recvfrom(mSock->getFd(), 
                          buff->toValue(), 
                          buff->size(), 
                          0, 
                          client_addr, 
                          (socklen_t *)&client_len);
    
    Inspect(length <= 0,nullptr)

    buff->quickShrink(length);
    return createSocketBuilder()
                ->setAddress(client->toInetAddress())
                ->setFileDescriptor(this->getFileDescriptor())
                ->newDatagramSocket();        
}

int _DatagramSocketImpl::connect() {
    //UDP do not need to do connect
    return 0;
}

int _DatagramSocketImpl::bind() {
    FetchRet(len,addr) = mAddress->getSockAddress()->get();
    return ::bind(mSock->getFd(),addr,len);
}

int _DatagramSocketImpl::write(ByteArray data,int start,int length) {
    FetchRet(addrlen,addr) = mAddress->getSockAddress()->get();
    struct sockaddr_in *addr_in = (struct sockaddr_in*)addr;
    int size = computeSutiableSize(data,start,length);
    return ::sendto(mSock->getFd(), data->toValue() + start, size, 0,addr, addrlen);
}

} // namespace obotcha