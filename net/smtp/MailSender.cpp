#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <time.h>

#include "FileInputStream.hpp"
#include "MailSender.hpp"
#include "Error.hpp"
#include "SSLInfo.hpp"

namespace obotcha {

SmtpCommandEntry _MailSender::SmtpCommandList[] = {
    {st(MailSender)::SmtpCommand::CommandINIT,          0,     5*60,  220, st(MailSender)::SmtpError::SERVER_NOT_RESPONDING},
    {st(MailSender)::SmtpCommand::CommandEHLO,          5*60,  5*60,  250, st(MailSender)::SmtpError::COMMAND_EHLO},
    {st(MailSender)::SmtpCommand::CommandAUTHPLAIN,     5*60,  5*60,  235, st(MailSender)::SmtpError::COMMAND_AUTH_PLAIN},
    {st(MailSender)::SmtpCommand::CommandAUTHLOGIN,     5*60,  5*60,  334, st(MailSender)::SmtpError::COMMAND_AUTH_LOGIN},
    {st(MailSender)::SmtpCommand::CommandAUTHCRAMMD5,   5*60,  5*60,  334, st(MailSender)::SmtpError::COMMAND_AUTH_CRAMMD5},
    {st(MailSender)::SmtpCommand::CommandAUTHDIGESTMD5, 5*60,  5*60,  334, st(MailSender)::SmtpError::COMMAND_AUTH_DIGESTMD5},
    {st(MailSender)::SmtpCommand::CommandDIGESTMD5,     5*60,  5*60,  335, st(MailSender)::SmtpError::COMMAND_DIGESTMD5},
    {st(MailSender)::SmtpCommand::CommandUSER,          5*60,  5*60,  334, st(MailSender)::SmtpError::UNDEF_XYZ_RESPONSE},
    {st(MailSender)::SmtpCommand::CommandPASSWORD,      5*60,  5*60,  235, st(MailSender)::SmtpError::BAD_LOGIN_PASS},
    {st(MailSender)::SmtpCommand::CommandMAILFROM,      5*60,  5*60,  250, st(MailSender)::SmtpError::COMMAND_MAIL_FROM},
    {st(MailSender)::SmtpCommand::CommandRCPTTO,        5*60,  5*60,  250, st(MailSender)::SmtpError::COMMAND_RCPT_TO},
    {st(MailSender)::SmtpCommand::CommandDATA,          5*60,  2*60,  354, st(MailSender)::SmtpError::COMMAND_DATA},
    {st(MailSender)::SmtpCommand::CommandDATABLOCK,     3*60,  0,     0,   st(MailSender)::SmtpError::COMMAND_DATABLOCK},    // Here the valid_reply_code is set to zero because there are no replies when sending data blocks
    {st(MailSender)::SmtpCommand::CommandDATAEND,       3*60,  10*60, 250, st(MailSender)::SmtpError::MSG_BODY_ERROR},
    {st(MailSender)::SmtpCommand::CommandQUIT,          5*60,  5*60,  221, st(MailSender)::SmtpError::COMMAND_QUIT},
    {st(MailSender)::SmtpCommand::CommandSTARTTLS,      5*60,  5*60,  220, st(MailSender)::SmtpError::COMMAND_EHLO_STARTTLS}
};

//------------ SmtpSimpleMd5 -------------------//
SmtpSimpleMd5::SmtpSimpleMd5() {
    MD5_Init(&md5);
}

void SmtpSimpleMd5::update(unsigned char *input, int input_length) {
    MD5_Update(&md5, input, input_length);
}

unsigned char *SmtpSimpleMd5::raw_digest() {
    unsigned char *md5_value = new unsigned char(MD5_DIGEST_LENGTH);
    MD5_Final(md5_value,&md5);
    return md5_value;
}

char *SmtpSimpleMd5::hex_digest() {
    unsigned char md5_value[MD5_DIGEST_LENGTH];
    MD5_Final(md5_value,&md5);
    char * output = new char(MD5_DIGEST_LENGTH*2 + 1);

    // convert md5 value to md5 string
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        snprintf(output + i*2, 2+1, "%02x", md5_value[i]);
    }
    return output;
}

void SmtpSimpleMd5::finalize() {
    //TODO
}

//------------ MailSenderBuilder ---------------//
_MailSenderBuilder::_MailSenderBuilder() {
    mSender = createMailSender();
}

sp<_MailSenderBuilder> _MailSenderBuilder::addRecipient(MailRecipient value) {
    mSender->mRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addRecipients(ArrayList<MailRecipient> value) {
    mSender->mRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addCcRecipient(MailRecipient value) {
    mSender->mCcRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addCcRecipients(ArrayList<MailRecipient> value) {
    mSender->mCcRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addBccRecipient(MailRecipient value) {
    mSender->mBccRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addBccRecipients(ArrayList<MailRecipient> value) {
    mSender->mBccRecipients->add(value);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addAttachment(File f) {
    mSender->mAttachments->add(f);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::addAttachments(ArrayList<File> files) {
    mSender->mAttachments->add(files);
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setMessage(String msg) {
    mSender->mMsgBody = msg;
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setConnection(SmtpConnection c) {
    mSender->mConnection = c;
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setReplyTo(String replyto) {
    mSender->mReplyTo = replyto;
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setPriority(int priority) {
    mSender->mPriority = priority;
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setSubject(String subject) {
    mSender->mSubject = subject;
    return AutoClone(this);
}

sp<_MailSenderBuilder> _MailSenderBuilder::setCharSet(String charset) {
    mSender->mCharSet = charset; 
    return AutoClone(this);
}

sp<_MailSender> _MailSenderBuilder::build() {
    return mSender;
}

//----------------------MailSender--------------------//
int _MailSender::WaitConnectTimeout = 3*60*1000;
int _MailSender::BuffSize = 10240;
int _MailSender::MaxAttachmentSize = 25*1024*1024;
String _MailSender::Boundary = createString("__MESSAGE__ID__54yg6f6h6y456345");

_MailSender::_MailSender() {
    mRecipients = createArrayList<MailRecipient>();
    mCcRecipients = createArrayList<MailRecipient>();
    mBccRecipients = createArrayList<MailRecipient>();
    mAttachments = createArrayList<File>();
    //mMsgBody = createArrayList<String>();

    mSendBuf = new char[BuffSize];
    mRecvBuf = new char[BuffSize];

    char hostname[255] = {0};
    if(gethostname((char *) &hostname, 255) == -1) {
        mHostName = createString("domain");
    } else {
        mHostName = createString(hostname);
    }

    mConnected = false;
    mPriority = Normal;

    mBase64 = createBase64();
    mCharSet = createString("utf-8");
    mMsgBody = nullptr;
}

_MailSender::~_MailSender() {
    disconnectRemoteServer();
    delete []mSendBuf;
    delete []mRecvBuf;
}

int _MailSender::send() {
    char *FileBuf = NULL;
	FILE* hFile = NULL;
    int res = 0;
    std::string fileName;
    std::string encodedFileName;
    printf("send trace1 \n");
    if(connectRemoteServer() != 0) {
        return -1;
    }
    printf("send trace1_1 \n");
    FileBuf = new char[55];

    unsigned long int totalsize = 0;

    ListIterator<File> iterator = this->mAttachments->getIterator();
    while(iterator->hasValue()) {
        File file = iterator->getValue();
        totalsize += file->length();
    }
    printf("send trace2 \n");
    if(totalsize > MaxAttachmentSize) {
        return -1;
    }
    printf("send trace3 \n");
    // ***** SENDING E-MAIL *****
    SmtpCommandEntry* pEntry;
    // MAIL <SP> FROM:<reverse-path> <CRLF>
	if(mConnection->mMailFrom != nullptr) {
        pEntry = getCommandEntry(CommandMAILFROM);
		snprintf(mSendBuf, BuffSize, "MAIL FROM:<%s>\r\n", mConnection->mMailFrom->toChars());
		sendData(pEntry);
		receiveResponse(pEntry);
    }
    printf("send trace4 \n");
    // RCPT <SP> TO:<forward-path> <CRLF>
    pEntry = getCommandEntry(CommandRCPTTO);
    ListIterator<MailRecipient> toIterator = mRecipients->getIterator();
    while(toIterator->hasValue()) {
        MailRecipient recipient = toIterator->getValue();
        snprintf(mSendBuf, BuffSize, "RCPT TO:<%s>\r\n", recipient->mail->toChars());
		sendData(pEntry);
		receiveResponse(pEntry);
        toIterator->next();
    }
    printf("send trace5 \n");
    toIterator = mCcRecipients->getIterator();
    while(toIterator->hasValue()) {
        MailRecipient recipient = toIterator->getValue();
        snprintf(mSendBuf, BuffSize, "RCPT TO:<%s>\r\n", recipient->mail->toChars());
		sendData(pEntry);
		receiveResponse(pEntry);
        toIterator->next();
    }
    printf("send trace6 \n");
    toIterator = mBccRecipients->getIterator();
    while(toIterator->hasValue()) {
        MailRecipient recipient = toIterator->getValue();
        snprintf(mSendBuf, BuffSize, "RCPT TO:<%s>\r\n", recipient->mail->toChars());
		sendData(pEntry);
		receiveResponse(pEntry);
        toIterator->next();
    }
    printf("send trace7 \n");
    pEntry = getCommandEntry(CommandDATA);
    // DATA <CRLF>
    snprintf(mSendBuf, BuffSize, "DATA\r\n");
    sendData(pEntry);
    receiveResponse(pEntry);
    printf("send trace8 \n");
    pEntry = getCommandEntry(CommandDATABLOCK);
    // send header(s)
    formatHeader(mSendBuf);
    sendData(pEntry);
    if(mMsgBody == nullptr) {
        snprintf(mSendBuf, BuffSize, "%s\r\n"," ");
    } else {
        snprintf(mSendBuf, BuffSize, "%s\r\n",mMsgBody->toChars());
    }
    sendData(pEntry);
    printf("send trace9 \n");
    // next goes attachments (if they are)
    ListIterator<File> attachIterator = mAttachments->getIterator();
    while(attachIterator->hasValue()) {
        File file = attachIterator->getValue();
        encodedFileName = "=?UTF-8?B?";
        encodedFileName += mBase64->encode(file->getName())->getStdString();
        encodedFileName += "?=";

        snprintf(mSendBuf, BuffSize, "--%s\r\n", Boundary->toChars());
        strcat(mSendBuf, "Content-Type: application/x-msdownload; name=\"");
        strcat(mSendBuf, encodedFileName.c_str());
        strcat(mSendBuf, "\"\r\n");
        strcat(mSendBuf, "Content-Transfer-Encoding: base64\r\n");
        strcat(mSendBuf, "Content-Disposition: attachment; filename=\"");
        strcat(mSendBuf, encodedFileName.c_str());
        strcat(mSendBuf, "\"\r\n");
        strcat(mSendBuf, "\r\n");

        sendData(pEntry);

        // opening the file:
        FileInputStream stream = createFileInputStream(file);
        stream->open();
        unsigned long int MsgPart = 0;
        long filesize = file->length();
        int index = 0;
        ByteArray readBuff = createByteArray(55);
        for(unsigned int i = 0;i<filesize/54+1;i++) {
            long length = stream->read(readBuff);
            MsgPart ? strcat(mSendBuf,(const char *)mBase64->encode(readBuff,res)->toValue())
                        : strcpy(mSendBuf,(const char *)mBase64->encode(readBuff,res)->toValue());
            strcat(mSendBuf,"\r\n");
            MsgPart += res + 2;
            if(MsgPart >= BuffSize/2) { // sending part of the message
                MsgPart = 0;
                sendData(pEntry); // FileBuf, FileName, fclose(hFile);
            }
        }
        if(MsgPart) {
            sendData(pEntry); // FileBuf, FileName, fclose(hFile);
        }
        stream->close();
        attachIterator->next();
    }
    printf("send trace10 \n");
    if(mAttachments->size()) {
		snprintf(mSendBuf, BuffSize, "\r\n--%s--\r\n",Boundary->toChars());
		sendData(pEntry);
	}
    printf("send trace11 \n");
    pEntry = getCommandEntry(CommandDATAEND);
    // <CRLF> . <CRLF>
    snprintf(mSendBuf, BuffSize, "\r\n.\r\n");
    sendData(pEntry);
    receiveResponse(pEntry);
}

int _MailSender::connectRemoteServer() {
    int res = 0;
    printf("connectRemoteServer trace1 \n");
    if((mConnection->mSocket = socket(PF_INET, SOCK_STREAM,0)) < 0) {
        return -OpenFail;
    }

    if(mConnection->mSmtpPort != 0) {
        mConnection->mSmtpPort = htons(mConnection->mSmtpPort);
    }

    struct sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = mConnection->mSmtpPort;
    const char *server = mConnection->mSmtpServer->toChars();
    if((sockAddr.sin_addr.s_addr = inet_addr(server)) == INADDR_NONE) {
        hostent* host = gethostbyname(server);
        if (host != nullptr) {
            memcpy(&sockAddr.sin_addr,host->h_addr_list[0],host->h_length);
        } else {
            return -OpenFail;
        }
    }
    printf("connectRemoteServer trace2 \n");
    unsigned long ul = 1;
    if(ioctl(mConnection->mSocket,FIONBIO, (unsigned long*)&ul) == -1) {
        close(mConnection->mSocket);
        return -OpenFail;
    }

    if(connect(mConnection->mSocket,(struct sockaddr *)&sockAddr,sizeof(sockAddr)) == -1) {
        if(errno != EINPROGRESS) {
            close(mConnection->mSocket);
            return -OpenFail;
        }
    } else {
        //TODO
        return true;
    }
    printf("connectRemoteServer trace3 \n");
    fd_set fdwrite;
    fd_set fdexcept;
    while(true) {
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdexcept);

        FD_SET(mConnection->mSocket,&fdwrite);
        FD_SET(mConnection->mSocket,&fdexcept);

        timeval timeout;
        timeout.tv_sec = WaitConnectTimeout/1000;
        timeout.tv_usec = (WaitConnectTimeout%1000)*1000;
        printf("connectRemoteServer trace4 \n");
        if((res = select(mConnection->mSocket + 1,NULL,&fdwrite,&fdexcept,&timeout)) == -1) {
            close(mConnection->mSocket);
            return -OpenFail;
        }

        if(!res) {
            close(mConnection->mSocket);
            return -OpenFail;
        }
        printf("connectRemoteServer trace5 \n");
        if(res && FD_ISSET(mConnection->mSocket,&fdwrite)) {
            break;
        }
                
        if(res && FD_ISSET(mConnection->mSocket,&fdexcept)) {
            close(mConnection->mSocket);
        }
    }//while
    printf("connectRemoteServer trace6 \n");
    FD_CLR(mConnection->mSocket,&fdwrite);
    FD_CLR(mConnection->mSocket,&fdexcept);

    if(mConnection->mSecurityType == st(SmtpConnection)::TLS || mConnection->mSecurityType == st(SmtpConnection)::SSL) {
        initOpenSSL();
        if(mConnection->mSecurityType == st(SmtpConnection)::SSL) {
            openSSLConnection();
        }
    }
    printf("connectRemoteServer trace7 \n");
    SmtpCommandEntry* pEntry = getCommandEntry(CommandINIT);
    receiveResponse(pEntry);

    sayHello();

    if(mConnection->mSecurityType == st(SmtpConnection)::SmtpSecurityType::TLS) {
        startTLS();
        sayHello();
    }
    printf("connectRemoteServer trace8，mRecvBuf is %s \n",mRecvBuf);
    if(mConnection->mAuthenticate && isKeywordSupported(mRecvBuf, "AUTH") == true) {
        if(isKeywordSupported(mRecvBuf, "LOGIN") == true) {
            printf("connectRemoteServer trace8 login 1 \n");
            pEntry = getCommandEntry(CommandAUTHLOGIN);
            snprintf(mSendBuf, BuffSize, "AUTH LOGIN\r\n");
            sendData(pEntry);
            receiveResponse(pEntry);
            printf("connectRemoteServer trace8 login 2 \n");

            // send login:
            std::string encoded_login = mBase64->encode(mConnection->mUsername)->getStdString();
            printf("connectRemoteServer trace8 encoded_login is %s 4_1 \n",mConnection->mUsername->toChars());
            printf("connectRemoteServer trace8 login encoded_login is %s 4 \n",encoded_login.c_str());
            pEntry = getCommandEntry(CommandUSER);
            snprintf(mSendBuf, BuffSize, "%s\r\n",encoded_login.c_str());
            sendData(pEntry);
            receiveResponse(pEntry);
            
            // send password:
            std::string encoded_password = mBase64->encode(mConnection->mPassword)->getStdString();
            printf("connectRemoteServer trace8 login password is %s 5_1 \n",mConnection->mPassword->toChars());
            printf("connectRemoteServer trace8 login encoded_password is %s 5 \n",encoded_password.c_str());
            pEntry = getCommandEntry(CommandPASSWORD);
            snprintf(mSendBuf, BuffSize, "%s\r\n",encoded_password.c_str());
            sendData(pEntry);
            receiveResponse(pEntry);
            printf("connectRemoteServer trace9 \n");
		} else if(isKeywordSupported(mRecvBuf, "PLAIN") == true) {
            pEntry = getCommandEntry(CommandAUTHPLAIN);
            snprintf(mSendBuf, BuffSize, "%s^%s^%s", 
                        mConnection->mUsername->toChars(),
                        mConnection->mUsername->toChars(), 
                        mConnection->mPassword->toChars());

            unsigned int length = strlen(mSendBuf);
            unsigned char *ustrLogin = charToUnsignedChar(mSendBuf);
            for(unsigned int i=0; i<length; i++) {
                if(ustrLogin[i]==94) ustrLogin[i]=0;
            }
            std::string encoded_login = mBase64->encode(createString((char *)ustrLogin, 0,length))->getStdString();
            delete[] ustrLogin;
            snprintf(mSendBuf, BuffSize, "AUTH PLAIN %s\r\n", encoded_login.c_str());
            sendData(pEntry);
            receiveResponse(pEntry);
            printf("connectRemoteServer trace10 \n");
        } else if(isKeywordSupported(mRecvBuf, "CRAM-MD5") == true) {
            pEntry = getCommandEntry(CommandAUTHCRAMMD5);
            snprintf(mSendBuf, BuffSize, "AUTH CRAM-MD5\r\n");
            sendData(pEntry);
            receiveResponse(pEntry);

            std::string encoded_challenge = mRecvBuf;
            encoded_challenge = encoded_challenge.substr(4);
            std::string decoded_challenge = mBase64->decode(createString(encoded_challenge))->getStdString();
            
            /////////////////////////////////////////////////////////////////////
            //test data from RFC 2195
            //decoded_challenge = "<1896.697170952@postoffice.reston.mci.net>";
            //m_sLogin = "tim";
            //m_sPassword = "tanstaaftanstaaf";
            //MD5 should produce b913a602c7eda7a495b4e6e7334d3890
            //should encode as dGltIGI5MTNhNjAyYzdlZGE3YTQ5NWI0ZTZlNzMzNGQzODkw
            /////////////////////////////////////////////////////////////////////

            unsigned char *ustrChallenge = charToUnsignedChar(decoded_challenge.c_str());
            unsigned char *ustrPassword = charToUnsignedChar(mConnection->mPassword->toChars());
            if(!ustrChallenge || !ustrPassword) {
                printf("connectRemoteServer trace11 \n");
                return-1;
            }
            // if ustrPassword is longer than 64 bytes reset it to ustrPassword=MD5(ustrPassword)
            int passwordLength = mConnection->mPassword->size();
            if(passwordLength > 64){
                //MD5 md5password;
                SmtpSimpleMd5 md5password;
                md5password.update(ustrPassword, passwordLength);
                md5password.finalize();
                ustrPassword = md5password.raw_digest();
                passwordLength = 16;
            }

            //Storing ustrPassword in pads
            unsigned char ipad[65], opad[65];
            memset(ipad, 0, 64);
            memset(opad, 0, 64);
            memcpy(ipad, ustrPassword, passwordLength);
            memcpy(opad, ustrPassword, passwordLength);

            // XOR ustrPassword with ipad and opad values
            for(int i=0; i<64; i++){
                ipad[i] ^= 0x36;
                opad[i] ^= 0x5c;
            }

            //perform inner MD5
            //MD5 md5pass1;
            SmtpSimpleMd5 md5pass1;
            md5pass1.update(ipad, 64);
            md5pass1.update(ustrChallenge, decoded_challenge.size());
            md5pass1.finalize();
            unsigned char *ustrResult = md5pass1.raw_digest();

            //perform outer MD5
            //MD5 md5pass2;
            SmtpSimpleMd5 md5pass2;
            md5pass2.update(opad, 64);
            md5pass2.update(ustrResult, 16);
            md5pass2.finalize();
            decoded_challenge = (char *)md5pass2.hex_digest();

            delete []ustrChallenge;
            delete []ustrPassword;
            delete ustrResult;

            decoded_challenge = mConnection->mUsername->getStdString() + " " + decoded_challenge;
            encoded_challenge = mBase64->encode(createString(decoded_challenge))->getStdString();
            snprintf(mSendBuf, BuffSize, "%s\r\n", encoded_challenge.c_str());
            pEntry = getCommandEntry(CommandPASSWORD);
            sendData(pEntry);
            receiveResponse(pEntry);
            printf("connectRemoteServer trace12 \n");
        } else if(isKeywordSupported(mRecvBuf, "DIGEST-MD5") == true) {
            printf("connectRemoteServer trace13 \n");
            pEntry = getCommandEntry(CommandDIGESTMD5);
            snprintf(mSendBuf, BuffSize, "AUTH DIGEST-MD5\r\n");
            sendData(pEntry);
            receiveResponse(pEntry);

            std::string encoded_challenge = mRecvBuf;
            encoded_challenge = encoded_challenge.substr(4);
            std::string decoded_challenge = mBase64->decode(createString(encoded_challenge))->getStdString();

            /////////////////////////////////////////////////////////////////////
            //Test data from RFC 2831
            //To test jump into authenticate and read this line and the ones down to next test data section
            //decoded_challenge = "realm=\"elwood.innosoft.com\",nonce=\"OA6MG9tEQGm2hh\",qop=\"auth\",algorithm=md5-sess,charset=utf-8";
            /////////////////////////////////////////////////////////////////////
            
            //Get the nonce (manditory)
            int find = decoded_challenge.find("nonce");
            if(find < 0) {
                return -1;
            }

            std::string nonce = decoded_challenge.substr(find+7);
            find = nonce.find("\"");
            if(find<0) {
                return -1;
            }

            nonce = nonce.substr(0, find);

            //Get the realm (optional)
            std::string realm;
            find = decoded_challenge.find("realm");
            if(find >= 0){
                realm = decoded_challenge.substr(find+7);
                find = realm.find("\"");
                if(find<0) {
                    return -1;
                }

                realm = realm.substr(0, find);
            }

            //Create a cnonce
            char cnonce[17], nc[9];
            snprintf(cnonce, 17, "%x", (unsigned int) time(NULL));

            //Set nonce count
            snprintf(nc, 9, "%08d", 1);

            //Set QOP
            std::string qop = "auth";

            //Get server address and set uri
            //Skip this step during test
            socklen_t len;

            struct sockaddr_storage addr;
            len = sizeof addr;
            if(!getpeername(mConnection->mSocket, (struct sockaddr*)&addr, &len)) {
                return -1;
            }

            struct sockaddr_in *s = (struct sockaddr_in *)&addr;
            std::string uri =inet_ntoa(s->sin_addr);
            uri = "smtp/" + uri;

            /////////////////////////////////////////////////////////////////////
            //test data from RFC 2831
            //m_sLogin = "chris";
            //m_sPassword = "secret";
            //snprintf(cnonce, 17, "OA6MHXh6VqTrRk");
            //uri = "imap/elwood.innosoft.com";
            //Should form the response:
            //    charset=utf-8,username="chris",
            //    realm="elwood.innosoft.com",nonce="OA6MG9tEQGm2hh",nc=00000001,
            //    cnonce="OA6MHXh6VqTrRk",digest-uri="imap/elwood.innosoft.com",
            //    response=d388dad90d4bbd760a152321f2143af7,qop=auth
            //This encodes to:
            //    Y2hhcnNldD11dGYtOCx1c2VybmFtZT0iY2hyaXMiLHJlYWxtPSJlbHdvb2
            //    QuaW5ub3NvZnQuY29tIixub25jZT0iT0E2TUc5dEVRR20yaGgiLG5jPTAw
            //    MDAwMDAxLGNub25jZT0iT0E2TUhYaDZWcVRyUmsiLGRpZ2VzdC11cmk9Im
            //    ltYXAvZWx3b29kLmlubm9zb2Z0LmNvbSIscmVzcG9uc2U9ZDM4OGRhZDkw
            //    ZDRiYmQ3NjBhMTUyMzIxZjIxNDNhZjcscW9wPWF1dGg=
            /////////////////////////////////////////////////////////////////////

            //Calculate digest response
            unsigned char *ustrRealm = charToUnsignedChar(realm.c_str());
            unsigned char *ustrUsername = charToUnsignedChar(mConnection->mUsername->toChars());
            unsigned char *ustrPassword = charToUnsignedChar(mConnection->mPassword->toChars());
            unsigned char *ustrNonce = charToUnsignedChar(nonce.c_str());
            unsigned char *ustrCNonce = charToUnsignedChar(cnonce);
            unsigned char *ustrUri = charToUnsignedChar(uri.c_str());
            unsigned char *ustrNc = charToUnsignedChar(nc);
            unsigned char *ustrQop = charToUnsignedChar(qop.c_str());
            if(!ustrRealm || !ustrUsername || !ustrPassword || !ustrNonce || !ustrCNonce || !ustrUri || !ustrNc || !ustrQop) {
                return -1;
            }

            //MD5 md5a1a;
            SmtpSimpleMd5 md5a1a;
            md5a1a.update(ustrUsername, mConnection->mUsername->size());
            md5a1a.update((unsigned char*)":", 1);
            md5a1a.update(ustrRealm, realm.size());
            md5a1a.update((unsigned char*)":", 1);
            md5a1a.update(ustrPassword, mConnection->mPassword->size());
            md5a1a.finalize();
            unsigned char *ua1 = md5a1a.raw_digest();

            //MD5 md5a1b;
            SmtpSimpleMd5 md5a1b;
            md5a1b.update(ua1, 16);
            md5a1b.update((unsigned char*)":", 1);
            md5a1b.update(ustrNonce, nonce.size());
            md5a1b.update((unsigned char*)":", 1);
            md5a1b.update(ustrCNonce, strlen(cnonce));
            //authzid could be added here
            md5a1b.finalize();
            char *a1 = (char *)md5a1b.hex_digest();
            
            //MD5 md5a2;
            SmtpSimpleMd5 md5a2;
            md5a2.update((unsigned char*) "AUTHENTICATE:", 13);
            md5a2.update(ustrUri, uri.size());
            //authint and authconf add an additional line here	
            md5a2.finalize();
            char *a2 = (char *)md5a2.hex_digest();

            delete ua1;
            ua1 = charToUnsignedChar(a1);
            unsigned char *ua2 = charToUnsignedChar(a2);
            
            //compute KD
            //MD5 md5;
            SmtpSimpleMd5 md5;
            md5.update(ua1, 32);
            md5.update((unsigned char*)":", 1);
            md5.update(ustrNonce, nonce.size());
            md5.update((unsigned char*)":", 1);
            md5.update(ustrNc, strlen(nc));
            md5.update((unsigned char*)":", 1);
            md5.update(ustrCNonce, strlen(cnonce));
            md5.update((unsigned char*)":", 1);
            md5.update(ustrQop, qop.size());
            md5.update((unsigned char*)":", 1);
            md5.update(ua2, 32);
            md5.finalize();
            decoded_challenge = (char *)md5.hex_digest();

            delete[] ustrRealm;
            delete[] ustrUsername;
            delete[] ustrPassword;
            delete[] ustrNonce;
            delete[] ustrCNonce;
            delete[] ustrUri;
            delete[] ustrNc;
            delete[] ustrQop;
            delete[] ua1;
            delete[] ua2;
            delete a1;
            delete a2;

            //send the response
            if(strstr(mRecvBuf, "charset") >=0 ) {
                snprintf(mSendBuf, BuffSize, "charset=utf-8,username=\"%s\"", mConnection->mUsername->toChars());
            } else {
                snprintf(mSendBuf, BuffSize, "username=\"%s\"", mConnection->mUsername->toChars());
            }
            if(!realm.empty()){
                snprintf(mRecvBuf, BuffSize, ",realm=\"%s\"", realm.c_str());
                strcat(mSendBuf, mRecvBuf);
            }
            snprintf(mRecvBuf, BuffSize, ",nonce=\"%s\"", nonce.c_str());
            strcat(mSendBuf, mRecvBuf);
            snprintf(mRecvBuf, BuffSize, ",nc=%s", nc);
            strcat(mSendBuf, mRecvBuf);
            snprintf(mRecvBuf, BuffSize, ",cnonce=\"%s\"", cnonce);
            strcat(mSendBuf, mRecvBuf);
            snprintf(mRecvBuf, BuffSize, ",digest-uri=\"%s\"", uri.c_str());
            strcat(mSendBuf, mRecvBuf);
            snprintf(mRecvBuf, BuffSize, ",response=%s", decoded_challenge.c_str());
            strcat(mSendBuf, mRecvBuf);
            snprintf(mRecvBuf, BuffSize, ",qop=%s", qop.c_str());
            strcat(mSendBuf, mRecvBuf);
            unsigned char *ustrDigest = charToUnsignedChar(mSendBuf);
            encoded_challenge = mBase64->encode(createString(ustrDigest))->getStdString();
            delete[] ustrDigest;
            snprintf(mSendBuf, BuffSize, "%s\r\n", encoded_challenge.c_str());
            pEntry = getCommandEntry(CommandDIGESTMD5);
            sendData(pEntry);
            receiveResponse(pEntry);

            //Send completion carraige return
            snprintf(mSendBuf, BuffSize, "\r\n");				
            pEntry = getCommandEntry(CommandPASSWORD);
            sendData(pEntry);
            receiveResponse(pEntry);
            printf("connectRemoteServer trace14 \n");
        }
    }
    //TODO
    printf("connectRemoteServer trace15 \n");
    return 0;
}

int _MailSender::disconnectRemoteServer() {
    if(mConnected) {
        sayQuit();
    }
	if(mConnection->mSocket >= 0)
	{
		close(mConnection->mSocket);
        mConnection->mSocket = -1;
	}

    return 0;
}

int _MailSender::initOpenSSL() {
    SSL_library_init();
    SSL_load_error_strings();
    mSSLContext = SSL_CTX_new (SSLv23_client_method());
    if(mSSLContext == NULL) {
        return -CreateFail; 
    }

    return 0;
}

int _MailSender::openSSLConnection() {
    if(mSSLContext == NULL) {
        return -InvalidParam;
    }

    mSSL = SSL_new (mSSLContext);   
    if(mSSL == NULL) {
        return -OpenFail;
    }
    SSL_set_fd (mSSL, (int)mConnection->mSocket);
    SSL_set_mode(mSSL, SSL_MODE_AUTO_RETRY);

    int res = 0;
    fd_set fdwrite;
    fd_set fdread;
    int write_blocked = 0;
    int read_blocked = 0;

    timeval time;
    time.tv_sec = WaitConnectTimeout/1000;
    time.tv_usec = (WaitConnectTimeout%1000)*1000;

    while(1) {
        FD_ZERO(&fdwrite);
        FD_ZERO(&fdread);

        if(write_blocked) {
            FD_SET(mConnection->mSocket, &fdwrite);
        }

        if(read_blocked)
            FD_SET(mConnection->mSocket, &fdread);

        if(write_blocked || read_blocked) {
            write_blocked = 0;
            read_blocked = 0;
            if((res = select(mConnection->mSocket +1,&fdread,&fdwrite,NULL,&time)) == -1) {
                FD_ZERO(&fdwrite);
                FD_ZERO(&fdread);
                return -OpenFail;
            }
            if(!res) {
                //timeout
                FD_ZERO(&fdwrite);
                FD_ZERO(&fdread);
                return -OpenFail;
            }
        }

        res = SSL_connect(mSSL);
        switch(SSL_get_error(mSSL, res)) {
          case SSL_ERROR_NONE:
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdread);
            return 0;
            break;
              
          case SSL_ERROR_WANT_WRITE:
            write_blocked = 1;
            break;

          case SSL_ERROR_WANT_READ:
            read_blocked = 1;
            break;
              
          default:          
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdread);
            return -WaitFail;
        }
    }
}

SmtpCommandEntry *_MailSender::getCommandEntry(int command) {
    SmtpCommandEntry* pEntry = nullptr;
    for(size_t i = 0; i < sizeof(SmtpCommandList)/sizeof(SmtpCommandList[0]); ++i) {
        if(SmtpCommandList[i].command == command) {
            pEntry = &SmtpCommandList[i];
            break;
        }
    }
    return pEntry;
}

int _MailSender::receiveDataSSL(SSL* ssl, SmtpCommandEntry* pEntry) {
    int res = 0;
    int offset = 0;
    fd_set fdread;
    fd_set fdwrite;
    timeval time;

    int read_blocked_on_write = 0;

    time.tv_sec = pEntry->recv_timeout;
    time.tv_usec = 0;

    bool bFinish = false;

    while(!bFinish) {
        FD_ZERO(&fdread);
        FD_ZERO(&fdwrite);

        FD_SET(mConnection->mSocket,&fdread);

        if(read_blocked_on_write) {
            FD_SET(mConnection->mSocket, &fdwrite);
        }

        if((res = select(mConnection->mSocket+1, &fdread, &fdwrite, NULL, &time)) == -1) {
            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            return -1;
        }

        if(!res) {
            //timeout
            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            return -1;
        }

        if(FD_ISSET(mConnection->mSocket,&fdread) || (read_blocked_on_write && FD_ISSET(mConnection->mSocket,&fdwrite))) {
            while(1) {
                read_blocked_on_write=0;

                const int buff_len = 1024;
                char buff[buff_len];

                res = SSL_read(ssl, buff, buff_len);

                int ssl_err = SSL_get_error(ssl, res);
                if(ssl_err == SSL_ERROR_NONE) {
                    if(offset + res > BuffSize - 1) {
                        FD_ZERO(&fdread);
                        FD_ZERO(&fdwrite);
                        return -1;
                    }
                    memcpy(mRecvBuf + offset, buff, res);
                    offset += res;
                    if(SSL_pending(ssl)) {
                        continue;
                    } else {
                        bFinish = true;
                        break;
                    }
                } else if(ssl_err == SSL_ERROR_ZERO_RETURN) {
                    bFinish = true;
                    break;
                } else if(ssl_err == SSL_ERROR_WANT_READ) {
                    break;
                } else if(ssl_err == SSL_ERROR_WANT_WRITE) {
                    /* We get a WANT_WRITE if we're
                    trying to rehandshake and we block on
                    a write during that rehandshake.

                    We need to wait on the socket to be 
                    writeable but reinitiate the read
                    when it is */
                    read_blocked_on_write=1;
                    break;
                } else {
                    FD_ZERO(&fdread);
                    FD_ZERO(&fdwrite);
                    return -1;
                }
            }
        }
    }

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    mRecvBuf[offset] = 0;
    if(offset == 0)
    {
        return -1;
    }

    return 0;
}

int _MailSender::sendDataSSL(SSL* ssl, SmtpCommandEntry* pEntry) {
    int offset = 0,res,nLeft = strlen(mSendBuf);
	fd_set fdwrite;
	fd_set fdread;
	timeval time;

	int write_blocked_on_read = 0;

	time.tv_sec = pEntry->send_timeout;
	time.tv_usec = 0;


	while(nLeft > 0) {
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdread);

		FD_SET(mConnection->mSocket,&fdwrite);

		if(write_blocked_on_read) {
			FD_SET(mConnection->mSocket, &fdread);
		}

		if((res = select(mConnection->mSocket+1,&fdread,&fdwrite,NULL,&time)) == -1)
		{
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
            return -1;
		}

		if(!res) {
			//timeout
			FD_ZERO(&fdwrite);
			FD_ZERO(&fdread);
            return -1;
		}

		if(FD_ISSET(mConnection->mSocket,&fdwrite) || (write_blocked_on_read && FD_ISSET(mConnection->mSocket, &fdread))){
			write_blocked_on_read=0;

			/* Try to write */
			res = SSL_write(ssl, mSendBuf+offset, nLeft);
	          
			switch(SSL_get_error(ssl,res)) {
			  /* We wrote something*/
			  case SSL_ERROR_NONE:
				nLeft -= res;
				offset += res;
				break;
	              
				/* We would have blocked */
			  case SSL_ERROR_WANT_WRITE:
				break;

				/* We get a WANT_READ if we're
				   trying to rehandshake and we block on
				   write during the current connection.
	               
				   We need to wait on the socket to be readable
				   but reinitiate our write when it is */
			  case SSL_ERROR_WANT_READ:
				write_blocked_on_read=1;
				break;
	              
				  /* Some other error */
			  default:	      
				FD_ZERO(&fdread);
				FD_ZERO(&fdwrite);
                return -1;
			}

		}
	}

	//OutputDebugStringA(SendBuf);
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdread);
}

int _MailSender::sendData(SmtpCommandEntry* pEntry) {
	if(mSSL != NULL)
	{
		return sendDataSSL(mSSL, pEntry);
	}
	int idx = 0,res,nLeft = strlen(mSendBuf);
	fd_set fdwrite;
	timeval time;

	time.tv_sec = pEntry->send_timeout;
	time.tv_usec = 0;


	while(nLeft > 0) {
		FD_ZERO(&fdwrite);

		FD_SET(mConnection->mSocket,&fdwrite);

		if((res = select(mConnection->mSocket+1,NULL,&fdwrite,NULL,&time)) == -1) {
			FD_CLR(mConnection->mSocket,&fdwrite);
            return -1;
		}

		if(!res) {
			//timeout
			FD_CLR(mConnection->mSocket,&fdwrite);
            return -1;
		}

		if(res && FD_ISSET(mConnection->mSocket,&fdwrite)) {
			res = ::send(mConnection->mSocket,&mSendBuf[idx],nLeft,0);
			if(res == -1 || res == 0)
			{
				FD_CLR(mConnection->mSocket,&fdwrite);
                return -1;
			}
			nLeft -= res;
			idx += res;
		}
	}

	//OutputDebugStringA(SendBuf);
	FD_CLR(mConnection->mSocket,&fdwrite);
}

int _MailSender::receiveData(SmtpCommandEntry* pEntry) {
    if(mSSL != NULL) {
        receiveDataSSL(mSSL, pEntry);
        return 0;
    }
    int res = 0;
    fd_set fdread;
    timeval time;

    time.tv_sec = pEntry->recv_timeout;
    time.tv_usec = 0;

    FD_ZERO(&fdread);

    FD_SET(mConnection->mSocket,&fdread);

    if((res = select(mConnection->mSocket+1, &fdread, NULL, NULL, &time)) == -1) {
        FD_CLR(mConnection->mSocket,&fdread);
        return -1;
    }

    if(!res) {
        //timeout
        FD_CLR(mConnection->mSocket,&fdread);
        return -1;
    }

    if(FD_ISSET(mConnection->mSocket,&fdread)) {
        res = recv(mConnection->mSocket,mRecvBuf,BuffSize,0);
        if(res == -1) {
            FD_CLR(mConnection->mSocket,&fdread);
            return -1;
        }
    }

    FD_CLR(mConnection->mSocket,&fdread);
    mRecvBuf[res] = 0;
    if(res == 0)
    {
        return -1;
    }

    return 0;
}

int _MailSender::receiveResponse(SmtpCommandEntry* pEntry)
{
    std::string line;
    int reply_code = 0;
    bool bFinish = false;
    while(!bFinish) {
        receiveData(pEntry);
        line.append(mRecvBuf);
        size_t len = line.length();
        size_t begin = 0;
        size_t offset = 0;

        while(1) {// loop for all lines
            while(offset + 1 < len) {
                if(line[offset] == '\r' && line[offset+1] == '\n')
                    break;
                ++offset;
            }
            if(offset + 1 < len) { // we found a line
            
                // see if this is the last line
                // the last line must match the pattern: XYZ<SP>*<CRLF> or XYZ<CRLF> where XYZ is a string of 3 digits 
                offset += 2; // skip <CRLF>
                if(offset - begin >= 5) {
                    if(isdigit(line[begin]) && isdigit(line[begin+1]) && isdigit(line[begin+2])) {
                        // this is the last line
                        if(offset - begin == 5 || line[begin+3] == ' ') {
                            reply_code = (line[begin]-'0')*100 + (line[begin+1]-'0')*10 + line[begin+2]-'0';
                            bFinish = true;
                            break;
                        }
                    }
                }
                begin = offset;    // try to find next line
            } else {// we haven't received the last line, so we need to receive more data 
                break;
            }
        }
    }

    snprintf(mRecvBuf, BuffSize, line.c_str());
    //OutputDebugStringA(RecvBuf);
    if(reply_code != pEntry->valid_reply_code) {
        return -1;
    }

    return 0;
}

int _MailSender::sayHello() {
    SmtpCommandEntry* pEntry = getCommandEntry(CommandEHLO);
    snprintf(mSendBuf, BuffSize, "EHLO %s\r\n", mHostName->toChars());
    if(sendData(pEntry) != 0) {
        return -1;
    }

    if(receiveResponse(pEntry) != 0) {
        return -1;
    }

    mConnected = true;
    return 0;
}

int _MailSender::sayQuit() {
    SmtpCommandEntry* pEntry = getCommandEntry(CommandQUIT);
    // QUIT <CRLF>
    snprintf(mSendBuf, BuffSize, "QUIT\r\n");
    mConnected=false;
    sendData(pEntry);
    receiveResponse(pEntry);
    return 0;
}

unsigned char* _MailSender::charToUnsignedChar(const char *strIn) {
	unsigned char *strOut;
	unsigned long length;
	unsigned long i;

	length = strlen(strIn);

	strOut = new unsigned char[length+1];
	if(!strOut) return NULL;

	for(i=0; i<length; i++) strOut[i] = (unsigned char) strIn[i];
	strOut[length]='\0';

	return strOut;
}

bool _MailSender::isKeywordSupported(const char* response, const char* keyword) {
    printf("isKeywordSupported start keyword is %s \n",keyword);
    if(response == NULL || keyword == NULL) {
        return false;
    }
    int res_len = strlen(response);
    int key_len = strlen(keyword);
    if(res_len < key_len) {
        return false;
    }
    printf("isKeywordSupported trace1 keyword is %s \n",keyword);
    int pos = 0;
    for(; pos < res_len - key_len + 1; ++pos) {
        if(strncasecmp(keyword, response+pos, key_len) == 0) {
            if(pos > 0 &&
                (response[pos - 1] == '-' ||
                 response[pos - 1] == ' ' ||
                 response[pos - 1] == '=')) {
                if(pos+key_len < res_len) {
                    if(response[pos+key_len] == ' ' ||
                       response[pos+key_len] == '=') {
                        printf("isKeywordSupported trace1_1 keyword is %s \n",keyword);
                        return true;
                    } else if(pos+key_len+1 < res_len) {
                        if(response[pos+key_len] == '\r' &&
                           response[pos+key_len+1] == '\n') {
                            printf("isKeywordSupported trace1_2 keyword is %s \n",keyword);
                            return true;
                        }
                    }
                }
            }
        }
    }
    printf("isKeywordSupported trace2 keyword is %s \n",keyword);
    return false;
}

int _MailSender::startTLS() {
    if(isKeywordSupported(mRecvBuf, "STARTTLS") == false) {
        return -1;
    }

    SmtpCommandEntry* pEntry = getCommandEntry(CommandSTARTTLS);
    snprintf(mSendBuf, BuffSize, "STARTTLS\r\n");
    if(sendData(pEntry) != 0) {
        return -1;
    }

    if(receiveResponse(pEntry) != 0) {
        return -1;
    }

    return openSSLConnection();
}

int _MailSender::formatHeader(char* header) {
	char month[][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	size_t i;
	std::string to;
	std::string cc;
	std::string bcc;
	time_t rawtime = time(0);
	struct tm timeinfo;

	// date/time check
	if(time(&rawtime) > 0) {
		localtime_r(&rawtime,&timeinfo);
    } else {
        return -1;
    }

	// check for at least one recipient
    ListIterator<MailRecipient> iterator = mRecipients->getIterator();
    int index = 0;
    while(iterator->hasValue()) {
        MailRecipient recipient = iterator->getValue();
        if(index > 0) {
            to.append(",");
        }
        to += recipient->name->getStdString();
        to.append("<");
        to += recipient->mail->getStdString();
        to.append(">");
        iterator->next();
        index++;
    }

    index = 0;
    iterator = mCcRecipients->getIterator();
    while(iterator->hasValue()) {
        MailRecipient recipient = iterator->getValue();
        if(index > 0) {
            cc.append(",");
        }
        cc += recipient->name->getStdString();
        cc.append("<");
        cc += recipient->mail->getStdString();
        cc.append(">");
        iterator->next();
        index++;
    }
	
	// Date: <SP> <dd> <SP> <mon> <SP> <yy> <SP> <hh> ":" <mm> ":" <ss> <SP> <zone> <CRLF>
	snprintf(header, BuffSize, "Date: %d %s %d %d:%d:%d\r\n", timeinfo.tm_mday,
	         month[timeinfo.tm_mon], timeinfo.tm_year+1900, timeinfo.tm_hour,
             timeinfo.tm_min, timeinfo.tm_sec); 
	
	// From: <SP> <sender>  <SP> "<" <sender-email> ">" <CRLF>
	strcat(header,"From: "); 
	strcat(header," <");
	strcat(header,mConnection->mMailFrom->toChars());
	strcat(header, ">\r\n");

	// X-Mailer: <SP> <xmailer-app> <CRLF>
	//if(m_sXMailer.size())
	//{
	//	strcat(header,"X-Mailer: ");
	//	strcat(header, m_sXMailer.c_str());
	//	strcat(header, "\r\n");
	//}

	// Reply-To: <SP> <reverse-path> <CRLF>
	if(mReplyTo != nullptr) {
		strcat(header, "Reply-To: ");
		strcat(header, mReplyTo->toChars());
		strcat(header, "\r\n");
	}

	// Disposition-Notification-To: <SP> <reverse-path or sender-email> <CRLF>
	//if(mReadReceipt) {
	//	strcat(header, "Disposition-Notification-To: ");
	//	if(m_sReplyTo.size()) strcat(header, m_sReplyTo.c_str());
	//	else strcat(header, m_sNameFrom.c_str());
	//	strcat(header, "\r\n");
	//}

	// X-Priority: <SP> <number> <CRLF>
	switch(mPriority) {
		case High:
			strcat(header,"X-Priority: 2 (High)\r\n");
			break;
		case Normal:
			strcat(header,"X-Priority: 3 (Normal)\r\n");
			break;
		case Low:
			strcat(header,"X-Priority: 4 (Low)\r\n");
			break;
		default:
			strcat(header,"X-Priority: 3 (Normal)\r\n");
	}

	// To: <SP> <remote-user-mail> <CRLF>
	strcat(header,"To: ");
	strcat(header, to.c_str());
	strcat(header, "\r\n");

	// Cc: <SP> <remote-user-mail> <CRLF>
	if(mCcRecipients->size()) {
		strcat(header,"Cc: ");
		strcat(header, cc.c_str());
		strcat(header, "\r\n");
	}

	//if(mBCcRecipients->size()) {
	//	strcat(header,"Bcc: ");
	//	strcat(header, bcc.c_str());
	//	strcat(header, "\r\n");
	//}

	// Subject: <SP> <subject-text> <CRLF>
	if(mSubject != nullptr) {
		strcat(header, "Subject: ");
        strcat(header, mSubject->toChars());
    } else {
	    strcat(header, "Subject: ");
	}

	strcat(header, "\r\n");
	
	// MIME-Version: <SP> 1.0 <CRLF>
	strcat(header,"MIME-Version: 1.0\r\n");
	if(mAttachments->size() != 0) { // no attachments
		strcat(header, "Content-type: text/plain; charset=\"");
		strcat(header, mCharSet->toChars());
		strcat(header, "\"\r\n");
		strcat(header,"Content-Transfer-Encoding: 7bit\r\n");
		strcat(mSendBuf,"\r\n");
	} else { // there is one or more attachments
		strcat(header,"Content-Type: multipart/mixed; boundary=\"");
		strcat(header,Boundary->toChars());
		strcat(header,"\"\r\n");
		strcat(header,"\r\n");
		// first goes text message
		strcat(mSendBuf,"--");
		strcat(mSendBuf,Boundary->toChars());
		strcat(mSendBuf,"\r\n");
		strcat(mSendBuf,"Content-type: text/plain; charset=");
		strcat(header, mCharSet->toChars());
		strcat(header, "\r\n");
		strcat(mSendBuf,"Content-Transfer-Encoding: 7bit\r\n");
		strcat(mSendBuf,"\r\n");
	}
	// done
    return 0;
}


}