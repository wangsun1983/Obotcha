#ifndef __OBOTCHA_SMTP_CONNECTION_HPP__
#define __OBOTCHA_SMTP_CONNECTION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

class _SmtpConnection;

DECLARE_SIMPLE_CLASS(MailRecipient) {
public:
    _MailRecipient();
    _MailRecipient(String,String);
    String name;
    String mail;
};

DECLARE_SIMPLE_CLASS(SmtpConnectionBuilder) {
public:
    _SmtpConnectionBuilder();
    sp<_SmtpConnectionBuilder> setHostName(String);
    sp<_SmtpConnectionBuilder> setMailFrom(String);
    sp<_SmtpConnectionBuilder> setNameFrom(String);
    sp<_SmtpConnectionBuilder> setSubject(String);
    sp<_SmtpConnectionBuilder> setReplyTo(String);
    sp<_SmtpConnectionBuilder> setUsername(String);
    sp<_SmtpConnectionBuilder> setPassword(String);
    sp<_SmtpConnectionBuilder> setSmtpServer(String);
    sp<_SmtpConnectionBuilder> setSecurityType(int);
    sp<_SmtpConnectionBuilder> setSmtpPort(int);
    sp<_SmtpConnectionBuilder> setAuthenticate(bool);
    
    sp<_SmtpConnection> build();
private:
    sp<_SmtpConnection> mConnection;
};

DECLARE_SIMPLE_CLASS(SmtpConnection) {

public:
    enum SmtpSecurityType {
        NoSecurity,
        TLS,
        SSL,
    };

    friend class _SmtpConnectionBuilder;
    friend class _MailSender;
    _SmtpConnection();
    String getHostName();
    String getMailFrom();
    String getNameFrom();
    String getSubject();
    String getReplyTo();
    String getUsername();
    String getPassword();
    String getSmtpServer();
    int getSmtpPort();
    bool isAuthenticate();

private:
    String mHostName;
    String mMailFrom;
    String mNameFrom;
    String mSubject;
    String mReplyTo;
    String mUsername;
    String mPassword;
    String mSmtpServer;
    int mSmtpPort;
    bool mAuthenticate;
    int mSecurityType;

    int mSocket;
};

}
#endif
