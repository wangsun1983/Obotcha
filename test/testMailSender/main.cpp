#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "MailSender.hpp"

using namespace obotcha;

int main() {
  SmtpConnectionBuilder connectionBuilder = createSmtpConnectionBuilder();
  SmtpConnection connection = connectionBuilder
                            ->setHostName(createString("abc"))
                            ->setSmtpServer(createString("smtp.163.com"))
                            ->setMailFrom(createString("wang_sun_1983@163.com"))
                            ->setUsername(createString("wang_sun_1983"))
                            ->setPassword(createString("ZPHYKJKMDTPVUJZO"))
                            ->setSubject(createString("hello title"))
                            ->build();
  
  MailSenderBuilder senderBuilder = createMailSenderBuilder();
  MailSender sender = senderBuilder->addRecipient(createMailRecipient("wangsl","wang_sun_1983@163.com"))
                                   ->setConnection(connection)
                                   ->setMessage("hello,i am obotcha")
                                   ->build();
  sender->send();
}
