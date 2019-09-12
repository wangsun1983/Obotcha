#include <stdio.h>

//#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(SimpleClass) {
public:
    int i;
    virtual void say() {
        printf("SimpleClass,hello \n");
    }
};

DECLARE_CLASS(SimpleClass2,0) EXTENDS(SimpleClass) {
public:
    int i;
    void say() {
        printf("SimpleClass2,hello \n");
    }
};

DECLARE_CLASS(Worker,1) {
public:
    int i;
    void  sayhello(T t) {
        printf("worker is %d \n",t);
    }
};

DECLARE_CLASS(Worker2,1) EXTENDS(Worker<T>){
public:
    void sayhello(T t) {
        printf("worker2 is %d \n",t);
    }
};

int normaltest()
{
    /*
    MyClass t = createMyClass(1,2);
        printf("t->v is %d \n",t->v);

        MyClass t2 = createMyClass(1.2);
        printf("t->v is %d \n",t2->v);
        printf("t->q is %f \n",t2->q);

        Mm t3 = createMm();
        t3->sayHello();


        //printf("create t ok \n");

        Student s = createStudent();
        s->sayHello();

        Pupile p = createPupile(1);
        p->sayHello();

    {
        //Pupile p = CreatePupile();
            //p->sayHello();
        // mystudent->incStrong();
      //mystudent->p = 123;
      //mystudent->i = 666;
                //mystudent->sayHello();
        //printf("mystudent.i is %d\n",mystudent->i);
        //printf("mystudent.p is %d\n",mystudent->p);
    }
*/

    //TTT<int> ss = createTTT<int>();
        //ss->sayhello(100);
#if 0
        Worker<int> t = createWorker<int>();
        t->sayhello(100);

        Worker2<int> t2 = createWorker2<int>();
        t2->sayhello(123);

        SimpleClass simple = createSimpleClass();
        simple->say();
#endif
    
        SimpleClass2 simple2 = createSimpleClass2();
        simple2->say();

        SimpleClass simple3 = simple2;
        simple3->say();

        SimpleClass2 simple4 = transform_cast<tp(SimpleClass2)>(simple3);
        //simple4->say();

    printf("end \n");


}
