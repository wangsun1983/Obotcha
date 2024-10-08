#include "SmtpConnection.hpp"
#include "MailRecipient.hpp"

namespace obotcha {
//--------------- MailRecipient ---------------------//
_MailRecipient::_MailRecipient(String param_name,String param_mail):
                                name(param_name),mail(param_mail) {
}

//--------------- SmtpConnection -----------------------//
_SmtpConnection::_SmtpConnection() {
    mAuthenticate = true;
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

int _SmtpConnection::getSmtpPort() const {
    return mSmtpPort;
}

bool _SmtpConnection::isAuthenticate() const {
    return mAuthenticate;
}

void _SmtpConnection::setHostName(String value) {
    this->mHostName = value;
    
}

void _SmtpConnection::setMailFrom(String value) {
    this->mMailFrom = value;
}

void _SmtpConnection::setNameFrom(String value) {
    this->mNameFrom = value;
}

void _SmtpConnection::setSubject(String value) {
    this->mSubject = value;
}

void _SmtpConnection::setReplyTo(String value) {
    this->mReplyTo = value;
}

void _SmtpConnection::setUsername(String value) {
    this->mUsername = value;
}

void _SmtpConnection::setPassword(String value) {
    this->mPassword = value;
}

void _SmtpConnection::setSmtpServer(String value) {
    this->mSmtpServer = value;
}

void _SmtpConnection::setSecurityType(_SmtpConnection::SecurityType value) {
    this->mSecurityType = value;
}

void _SmtpConnection::setSmtpPort(int value) {
    this->mSmtpPort = value;
}

void _SmtpConnection::setAuthenticate(bool value) {
    this->mAuthenticate = value;
}

}
