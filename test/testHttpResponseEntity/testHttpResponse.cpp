
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpResponseEntity.hpp"
#include "Reflect.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Student) {
public:
    int age;
    int no;

    DECLARE_REFLECT_FIELD(Student,age,no)
};

int main() {

    Student s = createStudent();
    s->age = 1;
    s->no = 100;

    HttpResponseEntity entity = createHttpResponseEntity(s);

    printf("entity is %s \n",entity->getContent()->get()->toChars());


}
