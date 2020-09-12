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

DECLARE_SIMPLE_CLASS(Student) {
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
