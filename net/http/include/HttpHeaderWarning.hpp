#ifndef __OBOTCHA_HTTP_HEADER_WARNING_HPP__
#define __OBOTCHA_HTTP_HEADER_WARNING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {

//Warning: <warn-code> <warn-agent> <warn-text> [<warn-date>]
DECLARE_CLASS(HttpHeaderWarning) {

public:
    _HttpHeaderWarning() = default;
    explicit _HttpHeaderWarning(String);

    void load(String);

    void setCode(int);
    void setAgent(String);
    void setText(String);
    void setDateTime(HttpDate);
    
    int getCode() const;
    String getAgent() const;
    String getText() const;
    HttpDate getDateTime() const;

    String toString() override;

    static const int ResponseIsStale;
    static const int RevalidationFailed;
    static const int DisconnectedOperation;
    static const int HeuristicExpiration;
    static const int MiscellaneousWarning;
    static const int TransformationApplied;
    static const int PersistentMiscellaneousWarning;

private:
    enum class ParseStatus {
        ParseCode = 0,
        ParseAgent,
        ParseText,
        ParseDate
    };
    
    void jumpSpace(const char *p,size_t &i,size_t size) const;

    int code = -1;
    String agent = nullptr;
    String text = nullptr;
    HttpDate date = nullptr;
};

}
#endif
