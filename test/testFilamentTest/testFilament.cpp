#include "Filament.hpp"

using namespace std;
using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        printf("MyRunn1 start \n");
        st(Filament)::yieldCurrent();
        printf("MyRunn1 sleep complete \n");
    }
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        printf("MyRunn2 start \n");
        st(Filament)::yieldCurrent();
        printf("MyRunn2 sleep complete \n");
    }
};

int main(void) {
    printf("main thread start \n");
    MyRun1 r1 = createMyRun1();
    MyRun2 r2 = createMyRun2();

    Filament f1 = createFilament(r1);
    Filament f2 = createFilament(r2);
    f1->resume();
    f2->resume();
    printf("main thread trace1 \n");
    f1->resume();
    f2->resume();
    printf("end \n");
}
