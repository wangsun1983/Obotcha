#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Sqlite3Connection.hpp"
#include "SqlConnection.hpp"
#include "Reflect.hpp"
#include "Sqlite3Client.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Student) {
public:
    int age;
    DECLARE_REFLECT_FIELD(Student,age)
};


int main() {

    HashMap<String,String> args = createHashMap<String,String>();
    args->put(st(Sqlite3Connection)::SQLITE3_CONNECT_TAG_PATH,"abc");
    Sqlite3Client c = createSqlite3Client();
    int result = c->connect(args);
    printf("result is %d \n",result);
/*
    ArrayList<SqlRecord> ss = c->query(createString("select * from student;"),RECORD_BUILDER(Student));
    if(ss == nullptr) {
        printf("query nullptr \n");
    }

    int size = ss->size();
    for(int index = 0;index<size;index++) {
        Student v = ss->get(index);
        printf("name is %s \n",v->getname()->toChars());
        printf("age is %d \n",v->getage());
    }

    while(1){}
*/
}
