#ifndef __OBOTCHA_SQL_CONDITION_VALUES_H__
#define __OBOTCHA_SQL_CONDITION_VALUES_H__

#include "Object.hpp"
#include "TextContent.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"
#include "SqlQuery.hpp"

namespace obotcha {

DECLARE_CLASS(SqlCondition) {
public:
    int mCondition;
    bool mIsString;
    String mTag;
    TextContent mValue;

    _SqlCondition(int condition,bool isString,String tag,TextContent content);
};

DECLARE_CLASS(SqlConditionValues) {
public:
    enum type {
        AND = 0,
        OR
    };

    _SqlConditionValues();

    template<typename T>
    void put(int condition,String tag,T value) {
        mConditions->add(createSqlCondition(condition,false,tag,
                                TextContent::New(value)));
    }

    template<typename T>
    void putString(int condition,String tag,T value) {
        mConditions->add(createSqlCondition(condition,true,tag,
                                TextContent::New(value)));
    }

private:
    ArrayList<SqlCondition> mConditions;
};

} // namespace obotcha
#endif