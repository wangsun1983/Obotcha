#ifndef __OBOTCHA_MAIL_SENDER_HPP__
#define __OBOTCHA_MAIL_SENDER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "SmtpConnection.hpp"
#include "File.hpp"
#include "Base64.hpp"
#include "Md.hpp"
#include "String.hpp"

extern "C" {
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/md5.h"
}

namespace obotcha {

class _MailSender;

struct SmtpCommandEntry {
	int command;
	int send_timeout;	 // 0 means no send is required
	int recv_timeout;	 // 0 means no recv is required
	int valid_reply_code; // 0 means no recv is required, so no reply code
	int error;
};

class SmtpSimpleMd5 {
public:
    SmtpSimpleMd5();
    void update(unsigned char *input, int input_length);
    unsigned char *raw_digest();
    char *hex_digest();
    void finalize();
private:
    MD5_CTX md5;
};

DECLARE_SIMPLE_CLASS(MailSenderBuilder) {
public:
    _MailSenderBuilder();
    sp<_MailSenderBuilder> addRecipient(MailRecipient);
    sp<_MailSenderBuilder> addRecipients(ArrayList<MailRecipient>);
    sp<_MailSenderBuilder> addCcRecipient(MailRecipient);
    sp<_MailSenderBuilder> addCcRecipients(ArrayList<MailRecipient>);
    sp<_MailSenderBuilder> addBccRecipient(MailRecipient);
    sp<_MailSenderBuilder> addBccRecipients(ArrayList<MailRecipient>);
    sp<_MailSenderBuilder> addAttachment(File);
    sp<_MailSenderBuilder> addAttachments(ArrayList<File>);
    sp<_MailSenderBuilder> setMessage(String);
    sp<_MailSenderBuilder> setConnection(SmtpConnection);
    sp<_MailSenderBuilder> setReplyTo(String);
    sp<_MailSenderBuilder> setPriority(int);
    sp<_MailSenderBuilder> setSubject(String);
    sp<_MailSenderBuilder> setCharSet(String);

    sp<_MailSender> build();
    
private:
    sp<_MailSender> mSender;
};

DECLARE_SIMPLE_CLASS(MailSender) {
public:
    friend class _MailSenderBuilder;
    _MailSender();
    ~_MailSender();

    int send();

    enum MailPriority {
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
    int mPriority;
    
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
};

}
#endif
