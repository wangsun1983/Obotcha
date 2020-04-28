#include "Filament.hpp"
#include <unistd.h>

using namespace std;
using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn1 start \n");
            sleep(1);
            st(Filament)::yieldCurrent();
            printf("MyRunn1 sleep complete \n");
        }
    }
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn2 start \n");
            sleep(1);
            st(Filament)::yieldCurrent();
            printf("MyRunn2 sleep complete \n");
        }
    }
};

DECLARE_SIMPLE_CLASS(MyRun3) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn3 start \n");
            sleep(1);
            st(Filament)::yieldCurrent();
            printf("MyRunn3 sleep complete \n");
        }
    }
};

int main(void) {
    printf("main thread start \n");
    MyRun1 r1 = createMyRun1();
    MyRun2 r2 = createMyRun2();
    MyRun3 r3 = createMyRun3();

    Filament f1 = createFilament(r1);
    Filament f2 = createFilament(r2);
    Filament f3 = createFilament(r3);
    f1->resume();
    f2->resume();
    f3->resume();
    printf("main thread trace1 \n");
    //f1->resume();
    //f2->resume();
    printf("end \n");
    while(1){}
}
