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
#include "SqlConnection.hpp"
#include <vector>

using namespace obotcha;


int testSimpleSql() {
    SqlConnection connection = createSqlConnection(MySqlConnection);

    HashMap<String,String> param = createHashMap<String,String>();
    param->put(createString("host"),createString("127.0.0.1"));
    param->put(createString("user"),createString("wangsun"));
    param->put(createString("password"),createString("01122982"));
    param->put(createString("dbname"),createString("student"));
    param->put(createString("port"),createString("3306"));
    int ret = connection->connect(param);
    /*
    ArrayList<Student> list = client->query<Student>(createSqlQuery("select * from information"));
    printf("list size is %d \n",list->size());
    ListIterator<Student> iterator = list->getIterator();
    while(iterator->hasValue()) {
        Student t = iterator->getValue();
        t->dump();
        iterator->next();
    }*/

    SqlRecords records = connection->query(createSqlQuery("select * from information"));
    SqlRecordsIterator iterator = records->getIterator();
    printf("wangsl,trace1 \n");
    while(iterator->hasValue()) {
        List<String> list = iterator->getRowData();
        for(int index = 0;index<list->size();index++) {
            printf("list[%d] is %s \n",index,list[index]->toChars());
        }
        iterator->next();
    }


}