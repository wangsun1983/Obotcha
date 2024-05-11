#ifndef __OBOTCHA_SQL_QUERY_H__
#define __OBOTCHA_SQL_QUERY_H__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

//#define PARAM_SEPREATE "_$"

DECLARE_CLASS(SqlQuery) {
public:
    explicit _SqlQuery(String);
    explicit _SqlQuery(const char *);
    _SqlQuery() = default;

    template <typename... T>
    void bindParam(T... args) {
        std::string str = mTemplate->getStdString();
        if(mTemplate != nullptr) {
            bind1(str,1,args...);
        }
        mSql = String::New(str);
    }

    String toString();
    String getTemplate();

private:
    
    template <typename T,typename... U>
    void bind1(std::string &ss,int index,T t,U... args) {
        std::string search = "_$";
        search.append(String::New(index)->getStdString());
        int startpos = ss.find(search);  
        if( startpos != std::string::npos ) {
            ss.replace(startpos,search.size(),String::New(t)->getStdString());
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