#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"
#include "MySqlClient.hpp"
#include "SqlQuery.hpp"
#include <vector>

using namespace obotcha;


int testSimpleSql() {
    SqlQuery query = createSqlQuery("abc is %1,dd is %2,%3,%4,%5,%6,%7");
    query->bindParam(5123,34444);
    printf("query is %s \n",query->toString()->toChars());
    printf("template is %s \n",query->getTemplate()->toChars());
}