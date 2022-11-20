#ifndef __OBOTCHA_HTTP_HEADER_WARNING_HPP__
#define __OBOTCHA_HTTP_HEADER_WARNING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

//Warning: <warn-code> <warn-agent> <warn-text> [<warn-date>]
DECLARE_CLASS(HttpHeaderWarning) {

public:
    _HttpHeaderWarning();
    _HttpHeaderWarning(String);

    void import(String);

    void setCode(int);
    void setAgent(String);
    void setText(String);
    void setDateTime(HttpDate);
    
    int getCode();
    String getAgent();
    String getText();
    HttpDate getDateTime();

    String toString();

    static const int ResponseIsStale;
    static const int RevalidationFailed;
    static const int DisconnectedOperation;
    static const int HeuristicExpiration;
    static const int MiscellaneousWarning;
    static const int TransformationApplied;
    static const int PersistentMiscellaneousWarning;

private:
    enum ParseStatus {
        ParseCode = 0,
        ParseAgent,
        ParseText,
        ParseDate
    };
    
    void jumpSpace(const char *p,int &i,int size);

    int code;
    String agent;
    String text;
    HttpDate date;
};

}
#endif
