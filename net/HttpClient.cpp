#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpClient.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"

namespace obotcha {

_HttpClient::_HttpClient() {
    //TODO
}

void _HttpClient::setIp(String ip) {

}

void _HttpClient::setUrl(String url) {

}

void _HttpClient::setPort(int port) {

}

void _HttpClient::setTimeout(int timeout) {

}

void _HttpClient::setKeepAlive(bool keepalive) {

}

String _HttpClient::getIp() {

}

String _HttpClient::getUrl() {

}

int _HttpClient::getPort() {

}

int _HttpClient::getTimeout() {

}

bool _HttpClient::getKeepAlive() {
   
}

int _HttpClient::connect() {

}

int _HttpClient::execute(int method,HttpUrl url) {
    HttpPacket packet = createHttpPacket();
    packet->setMethod(method);
    packet->setUrl(url->getPath());

    //we need get ip for url
    ArrayList<String> ips = st(InetAddress)::getHostByName(url->getHost());
    ListIterator<String> iterator = ips->getIterator();
    while(iterator->hasValue()) {
        printf("ip is %s \n",iterator->getValue()->toChars());
        iterator->next();
    }
    //mTcpClient = createTcpClient();
}

int _HttpClient::execute(int,String url) {
    //TODO
}

}

