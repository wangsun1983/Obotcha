#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Reflect.hpp"
#include "Sqlite3Client.hpp"

using namespace obotcha;

DECLARE_CLASS(Student) {
public:
    int age;
    int id;
    String name;

    void dump() {
        printf("name is %s ,age is %d,id is %d \n",name->toChars(),age,id);
    }

    DECLARE_REFLECT_FIELD(Student,age,id,name)
};


int main() {
    /*
    HashMap<String,String> args = createHashMap<String,String>();
    args->put(st(Sqlite3Client)::SQLITE3_CONNECT_TAG_PATH,"abc");
    Sqlite3Client c = createSqlite3Client();
    c->connect(args);

    ArrayList<Student> result = c->query<Student>(createString("select * from student;"));
    ListIterator<Student> iterator = result->getIterator();
    while(iterator->hasValue()) {
        Student ss = iterator->getValue();
        ss->dump();
        iterator->next();
    }
    */

    HashMap<String,String> args = createHashMap<String,String>();
    args->put(st(Sqlite3Client)::SQLITE3_CONNECT_TAG_PATH,"abc");
    Sqlite3Client c = createSqlite3Client();
    c->connect(args);

    SqlRecords records = c->query(createSqlQuery("select * from student"));
    SqlRecordsIterator iterator = records->getIterator();
    printf("wangsl,trace1 \n");
    while(iterator->hasValue()) {
        List<String> list = iterator->getRowData();
        for(int index = 0;index<list->size();index++) {
            printf("list[%d] is %s \n",index,list[index]->toChars());
        }
        iterator->next();
    }

    while(1){}

}
