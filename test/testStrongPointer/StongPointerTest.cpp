#include <stdio.h>

//#include "Object.hpp"
#include "StrongPointer.hpp"

/*
#define localclass _MyClass


#define DECLARE_M_CLASS(Y) \
class _##Y;\
typedef sp<_##Y> Y;\
template<typename... Args>\
sp<_##Y> create##Y(Args&&... args)\
{\
    sp<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
		return ret;\
}\
class _##Y: virtual public obo::Object\

#define CONSTRUCT(X) _##X

#define DESTRUCT(X) ~_##X

#define EXTENDS(X) ,virtual public _##X

#define IMPLEMENTS(X) ,virtual public _##X
*/

/*
DECLARE_CLASS(MyClass) {
public:
	int v;
	float q;

	CONSTRUCT(MyClass)(double t) {
		q = t;
		v = 111;
	}

	CONSTRUCT(MyClass)() {
		v = -1;
	}

	CONSTRUCT(MyClass)(int i) {
		v = i;
	}

	CONSTRUCT(MyClass)(int i,int j) {
		v = i+j;
	}

	DESTRUCT(MyClass)(){}
};

DECLARE_CLASS (Mm) {
public:
	int p;
  CONSTRUCT(Mm)(){printf("init i \n");}
	void sayHello() {
		printf("i am mm \n");
	}
};


DECLARE_CLASS(Mm1) {
public :
    int p;
    DESTRUCT(Mm1)() {
    	printf("Mm1 release \n");
    }

		void sayHello() {
			printf("i am mm1 \n");
		}

};

DECLARE_CLASS(Student) EXTENDS(Mm1) {

public:
	int i;

	DESTRUCT(Student)() {
		printf("Student release \n");
	}

	void sayHello() {
		printf("i am Student \n");
	}

};

DECLARE_CLASS(Pupile) EXTENDS(Mm1) {
public:
	int j;

	CONSTRUCT(Pupile)(){printf("puiple create \n");}

  CONSTRUCT(Pupile)(int i){printf("puiple create ,i is %d\n",i);}
};
*/

/*
#define CLASS_M_PRE_DEF_1(Y) template<typename X>class _##Y
#define TYPE_M_DEF_1(Y) \
template<typename U> \
using Y = sp<_##Y<U>>

CLASS_M_PRE_DEF_1(TTT);
TYPE_M_DEF_1(TTT);

template<typename Y>
sp<_TTT<Y>> createTTT(){
	sp<_TTT<Y>> ret = new _TTT<Y>();
	return ret;
}

template<typename T>
class _TTT :virtual public obo::Object{
	public:
		 void sayhello(T t) {
		    printf("ttt is %d \n",t);
	   }
};
*/
DECLARE_SIMPLE_CLASS(SimpleClass) {
public:
	int i;
	void say() {
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

int main()
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

		Worker<int> t = createWorker<int>();
		t->sayhello(100);

		Worker2<int> t2 = createWorker2<int>();
		t2->sayhello(123);

		SimpleClass simple = createSimpleClass();
		simple->say();

    SimpleClass2 simple2 = createSimpleClass2();
		simple2->say();

    printf("end \n");


}
