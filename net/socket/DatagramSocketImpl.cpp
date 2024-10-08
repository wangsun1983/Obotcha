/**
 * @file DatagramSocketImpl.cpp
 * @brief datagram and multicast socket implementation base class.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-17
 * @license none
 */

#include "DatagramSocketImpl.hpp"
#include "FileDescriptor.hpp"
#include "InitializeException.hpp"
#include "Socket.hpp"
#include "Inspect.hpp"
#include "SocketBuilder.hpp"
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
    mSock = FileDescriptor::New(TEMP_FAILURE_RETRY(socket(address->getSockAddress()->family(), 
                                SOCK_DGRAM,
                                IPPROTO_UDP)));
    
    if (mSock->getFd() < 0) {
        LOG(ERROR)<<"DatagramSocket open fd failed,reason is "<<strerror(errno);
        Trigger(InitializeException, "Datagram Socket create failed")
    }

    if(option != nullptr) {
        option->update(mSock);
    }
}

Socket _DatagramSocketImpl::recvDatagram(ByteArray buff) {
    SockAddress client = SockAddress::New(mAddress->getFamily());
    FetchRet(client_len,client_addr) = client->get();
    ssize_t length = recvfrom(mSock->getFd(), 
                          buff->toValue(), 
                          buff->size(), 
                          0, 
                          client_addr, 
                          (socklen_t *)&client_len);
    Inspect(length <= 0,nullptr)

    buff->quickShrink(length);
    return SocketBuilder::New()
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

ssize_t _DatagramSocketImpl::write(ByteArray data,uint64_t start,uint64_t length) {
    FetchRet(addrlen,addr) = mAddress->getSockAddress()->get();
    size_t size = computeSutiableSize(data,start,length);
    return ::sendto(mSock->getFd(), data->toValue() + start, size, 0,addr, addrlen);
}

} // namespace obotcha