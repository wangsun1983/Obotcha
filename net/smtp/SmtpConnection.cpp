#include "SmtpConnection.hpp"

namespace obotcha {

//--------------- SmtpConnectionBuilder -----------------------//
_SmtpConnectionBuilder::_SmtpConnectionBuilder() {
    mConnection = createSmtpConnection();
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setHostName(String value) {
    mConnection->mHostName = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setMailFrom(String value) {
    mConnection->mMailFrom = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setNameFrom(String value) {
    mConnection->mNameFrom = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setSubject(String value) {
    mConnection->mSubject = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setReplyTo(String value) {
    mConnection->mReplyTo = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setUsername(String value) {
    mConnection->mUsername = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setPassword(String value) {
    mConnection->mPassword = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setSmtpServer(String value) {
    mConnection->mSmtpServer = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setSecurityType(int value) {
    mConnection->mSecurityType = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setSmtpPort(int value) {
    mConnection->mSmtpPort = value;
}

sp<_SmtpConnectionBuilder> _SmtpConnectionBuilder::setAuthenticate(bool value) {
    mConnection->mAuthenticate = value;
}

sp<_SmtpConnection> _SmtpConnectionBuilder::build() {
    return mConnection;
}

//--------------- SmtpConnection -----------------------//

_SmtpConnection::_SmtpConnection() {
    mSecurityType = NoSecurity;
}

String _SmtpConnection::getHostName() {
    return mHostName;
}

String _SmtpConnection::getMailFrom() {
    return this->mMailFrom;
}

String _SmtpConnection::getNameFrom() {
    return this->mNameFrom;
}

String _SmtpConnection::getSubject() {
    return this->mSubject;
}

String _SmtpConnection::getReplyTo() {
    return this->mReplyTo;
}

String _SmtpConnection::getUsername() {
    return this->mUsername;
}

String _SmtpConnection::getPassword() {
    return this->mPassword;
}

String _SmtpConnection::getSmtpServer() {
    return this->mSmtpServer;
}

int _SmtpConnection::getSmtpPort() {
    return mSmtpPort;
}

bool _SmtpConnection::isAuthenticate() {
    return mAuthenticate;
}


}
