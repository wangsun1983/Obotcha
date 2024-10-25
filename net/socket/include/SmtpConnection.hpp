#ifndef __OBOTCHA_SMTP_CONNECTION_HPP__
#define __OBOTCHA_SMTP_CONNECTION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class _SmtpConnection;

DECLARE_CLASS(SmtpConnection) {

public:
    enum class SecurityType {
        NoSecurity = 0,
        TLS,
        SSL,
    };

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
    int getSmtpPort() const;
    bool isAuthenticate() const;

    void setHostName(String);
    void setMailFrom(String);
    void setNameFrom(String);
    void setSubject(String);
    void setReplyTo(String);
    void setUsername(String);
    void setPassword(String);
    void setSmtpServer(String);
    void setSecurityType(SecurityType);
    void setSmtpPort(int);
    void setAuthenticate(bool);

private:
    String mHostName;
    String mMailFrom;
    String mNameFrom;
    String mSubject;
    String mReplyTo;
    String mUsername;
    String mPassword;
    String mSmtpServer;
    int mSmtpPort = 25;
    bool mAuthenticate;
    SecurityType mSecurityType = _SmtpConnection::SecurityType::NoSecurity;

    int mSocket;
};

}
#endif
