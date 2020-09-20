#ifndef __OBOTCHA_SQL_QUERY_H__
#define __OBOTCHA_SQL_QUERY_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SqlQuery) {
public:
    _SqlQuery(String);
    _SqlQuery(const char *);
    _SqlQuery();

    template <typename... T>
    void bindParam(T... args) {
        std::string str = mTemplate->getStdString();
        if(mTemplate != nullptr) {
            bind1(str,1,args...);
        }
        mSql = createString(str);
    }

    String toString();
    String getTemplate();

private:
    std::string toStr(byte);
    std::string toStr(double);
    std::string toStr(float);
    std::string toStr(int);
    std::string toStr(long);
    std::string toStr(uint16_t);
    std::string toStr(uint32_t);
    std::string toStr(uint64_t);
    std::string toStr(String);
    std::string toStr(const char *);

    template<typename T>
    std::string toStr(T v) {
        String str = v->toString();
        return str->getStdString();
    }

    template <typename T,typename... U>
    void bind1(std::string &ss,int index,T t,U... args) {
        std::string search = "%";
        search.append(toStr(index));
        int startpos = ss.find(search);  
        if( startpos != std::string::npos ) {
            ss.replace(startpos,search.size(),toStr(t));
        }
        index++;
        bind1(ss,index,args...);
    }

    void bind1(std::string ss,int index) {
	    return;
    }

    String mTemplate;
    String mSql;
};

} // namespace obotcha
#endif