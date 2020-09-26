#include  "SqlQuery.hpp"

namespace obotcha {

_SqlQuery::_SqlQuery(String sql) {
    mTemplate = sql;
}

_SqlQuery::_SqlQuery(const char *sql) {
    mTemplate = createString(sql);
}

_SqlQuery::_SqlQuery() {
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

std::string _SqlQuery::toStr(byte v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(double v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(float v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(int v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(long v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(uint16_t v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(uint32_t v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(uint64_t v) {
    return std::to_string(v);
}

std::string _SqlQuery::toStr(String v) {
    return v->getStdString();
}

std::string _SqlQuery::toStr(const char *v) {
    return std::string(v);
}
    

}