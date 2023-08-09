#ifndef __OBOTCHA_MAIL_SENDER_HPP__
#define __OBOTCHA_MAIL_SENDER_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "SmtpConnection.hpp"
#include "File.hpp"
#include "Base64.hpp"
#include "Md.hpp"
#include "String.hpp"
#include "MailRecipient.hpp"

extern "C" {
    #include "openssl/ssl.h"
    #include "openssl/err.h"
    #include "openssl/md5.h"
}

namespace obotcha {

class _MailSenderBuilder;

struct SmtpCommandEntry {
	int command;
	int send_timeout;	 // 0 means no send is required
	int recv_timeout;	 // 0 means no recv is required
	int valid_reply_code; // 0 means no recv is required, so no reply code
	int error;
};

DECLARE_CLASS(MailSender) {
public:
    friend class _MailSenderBuilder;
    _MailSender();
    ~_MailSender() override;

    int send();

    enum class MailPriority {
        High = 0,
        Normal,
        Low
    };

private:
    enum SmtpCommand {
        CommandINIT,
        CommandEHLO,
        CommandAUTHPLAIN,
        CommandAUTHLOGIN,
        CommandAUTHCRAMMD5,
        CommandAUTHDIGESTMD5,
        CommandDIGESTMD5,
        CommandUSER,
        CommandPASSWORD,
        CommandMAILFROM,
        CommandRCPTTO,
        CommandDATA,
        CommandDATABLOCK,
        CommandDATAEND,
        CommandQUIT,
        CommandSTARTTLS
    };

    enum SmtpError
	{
		CSMTP_NO_ERROR = 0,
		WSA_STARTUP = 100, // WSAGetLastError()
		WSA_VER,
		WSA_SEND,
		WSA_RECV,
		WSA_CONNECT,
		WSA_GETHOSTBY_NAME_ADDR,
		WSA_INVALID_SOCKET,
		WSA_HOSTNAME,
		WSA_IOCTLSOCKET,
		WSA_SELECT,
		BAD_IPV4_ADDR,
		UNDEF_MSG_HEADER = 200,
		UNDEF_MAIL_FROM,
		UNDEF_SUBJECT,
		UNDEF_RECIPIENTS,
		UNDEF_LOGIN,
		UNDEF_PASSWORD,
		BAD_LOGIN_PASSWORD,
		BAD_DIGEST_RESPONSE,
		BAD_SERVER_NAME,
		UNDEF_RECIPIENT_MAIL,
		COMMAND_MAIL_FROM = 300,
		COMMAND_EHLO,
		COMMAND_AUTH_PLAIN,
		COMMAND_AUTH_LOGIN,
		COMMAND_AUTH_CRAMMD5,
		COMMAND_AUTH_DIGESTMD5,
		COMMAND_DIGESTMD5,
		COMMAND_DATA,
		COMMAND_QUIT,
		COMMAND_RCPT_TO,
		MSG_BODY_ERROR,
		CONNECTION_CLOSED = 400, // by server
		SERVER_NOT_READY, // remote server
		SERVER_NOT_RESPONDING,
		SELECT_TIMEOUT,
		FILE_NOT_EXIST,
		MSG_TOO_BIG,
		BAD_LOGIN_PASS,
		UNDEF_XYZ_RESPONSE,
		LACK_OF_MEMORY,
		TIME_ERROR,
		RECVBUF_IS_EMPTY,
		SENDBUF_IS_EMPTY,
		OUT_OF_MSG_RANGE,
		COMMAND_EHLO_STARTTLS,
		SSL_PROBLEM,
		COMMAND_DATABLOCK,
		STARTTLS_NOT_SUPPORTED,
		LOGIN_NOT_SUPPORTED
	};

    static SmtpCommandEntry SmtpCommandList[];

    ArrayList<MailRecipient> mRecipients;
    ArrayList<MailRecipient> mCcRecipients;
    ArrayList<MailRecipient> mBccRecipients;
    ArrayList<File> mAttachments;
    String mMsgBody;
    String mSubject;
    SmtpConnection mConnection;
    String mReplyTo;
    String mCharSet;
    _MailSender::MailPriority mPriority = _MailSender::MailPriority::Normal;
    
    static int WaitConnectTimeout;
    static int BuffSize;
    static int MaxAttachmentSize;
    static String Boundary;

    SSL_CTX*  mSSLContext;
	SSL*  mSSL;

    int connectRemoteServer();
    int disconnectRemoteServer();

    int initOpenSSL();
    int openSSLConnection();
    SmtpCommandEntry *getCommandEntry(int);
    int receiveResponse(SmtpCommandEntry* pEntry);
    int receiveData(SmtpCommandEntry* pEntry);
    int receiveDataSSL(SSL* ssl, SmtpCommandEntry* pEntry);
    int sendData(SmtpCommandEntry* pEntry);
    int sendDataSSL(SSL* ssl, SmtpCommandEntry* pEntry);
    int sayHello();
	int sayQuit();
    int startTLS();
    bool isKeywordSupported(const char* response, const char* keyword);
    unsigned char* charToUnsignedChar(const char *strIn);
    int formatHeader(char* header);

    String mHostName;
    bool mConnected;

    char *mSendBuf;
	char *mRecvBuf;
    Base64 mBase64;
    Md mMd;
};

DECLARE_CLASS(MailSenderBuilder) {
public:
    _MailSenderBuilder();
    _MailSenderBuilder * addRecipient(MailRecipient);
    _MailSenderBuilder * addRecipients(ArrayList<MailRecipient>);
    _MailSenderBuilder * addCcRecipient(MailRecipient);
    _MailSenderBuilder * addCcRecipients(ArrayList<MailRecipient>);
    _MailSenderBuilder * addBccRecipient(MailRecipient);
    _MailSenderBuilder * addBccRecipients(ArrayList<MailRecipient>);
    _MailSenderBuilder * addAttachment(File);
    _MailSenderBuilder * addAttachments(ArrayList<File>);
    _MailSenderBuilder * setMessage(String);
    _MailSenderBuilder * setConnection(SmtpConnection);
    _MailSenderBuilder * setReplyTo(String);
    _MailSenderBuilder * setPriority(_MailSender::MailPriority);
    _MailSenderBuilder * setSubject(String);
    _MailSenderBuilder * setCharSet(String);

    sp<_MailSender> build();
    
private:
    sp<_MailSender> mSender;
};

}
#endif
