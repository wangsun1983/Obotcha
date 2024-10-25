#ifndef __OBOTCHA_MAIL_RECIPIENT_HPP__
#define __OBOTCHA_MAIL_RECIPIENT_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(MailRecipient) {
public:
    _MailRecipient() = default;
    _MailRecipient(String,String);
    String name;
    String mail;
};

}

#endif