#include "SqlConditionValues.hpp"

namespace obotcha {

_SqlCondition::_SqlCondition(int condition,bool isString,String tag,TextContent content) {
    mCondition = condition;
    mTag = tag;
    mValue = content;
    mIsString = isString;
}

_SqlConditionValues::_SqlConditionValues() {
    mConditions = createArrayList<SqlCondition>();
}



} // namespace obotcha
