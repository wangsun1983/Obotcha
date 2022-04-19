#ifndef __OBOTCHA_MAIL_RECIPIENT_HPP__
#define __OBOTCHA_MAIL_RECIPIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(MailRecipient) {
public:
    _MailRecipient();
    _MailRecipient(String,String);
    String name;
    String mail;
};

}

#endif