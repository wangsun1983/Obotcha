#include  "SqlQuery.hpp"

namespace obotcha {

_SqlQuery::_SqlQuery(String sql) {
    mTemplate = sql;
}

_SqlQuery::_SqlQuery(const char *sql) {
    mTemplate = createString(sql);
}

String _SqlQuery::toString() {
    if(mSql != nullptr) {
        return mSql;
    }

    return mTemplate;
}

String _SqlQuery::getTemplate() {
    return mTemplate;
}

}