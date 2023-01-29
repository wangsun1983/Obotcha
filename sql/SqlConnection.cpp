#include "SqlConnection.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_SqlConnection::_SqlConnection() {
    mType = -1;
}

int _SqlConnection::insert(String table,SqlContentValues values) {
    SqlQuery query = createSqlQuery("INSERT INTO _$1 _$2 VALUES _$3;");
    query->bindParam(table,values->getTags(),values->getValues());
    return exec(query);
}

int _SqlConnection::update(String table,SqlContentValues values,SqlQuery condition) {
    SqlQuery query = createSqlQuery("UPDATE _$1 SET _$2 WHERE _$3;");

    auto map = values->getContentValues();
    StringBuffer buffer = createStringBuffer();
    ForEveryOne(pair,map) {
        String name = pair->getKey();
        auto content = pair->getValue();
        String value = content->mContent->get();
        if(!content->isStringContent) {
            buffer->append(name," = ",value,",");
        } else {
            buffer->append(name," = \"",value,"\",");
        }
    }

    buffer->subString(0,buffer->size() - 1);
    query->bindParam(table,buffer->toString(),condition->toString());
    return exec(query);
}

int _SqlConnection::erase(String table,SqlQuery condition) {
    SqlQuery query = createSqlQuery("DELETE FROM _$1 WHERE _$2;");
    query->bindParam(table,condition->toString());
    return exec(query);
}

int _SqlConnection::create(String table,SqlTableEntryValues values) {
    SqlQuery query = createSqlQuery("CREATE TABLE _$1(_$2);");
    query->bindParam(table,values->toString());
    printf("create sql is %s \n",query->toString()->toChars());
    return exec(query);
}

}
