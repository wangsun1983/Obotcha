#include "Filament.hpp"
#include "ArrayList.hpp"
#include "FilaCroutine.hpp"
#include <unistd.h>

using namespace std;
using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn1 start \n");
            poll(NULL, 0, 500);
        }
    }
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn2 start \n");
            poll(NULL, 0, 1000);
        }
    }
};

DECLARE_SIMPLE_CLASS(MyRun3) IMPLEMENTS(FilaRunnable) {
public:
    void run() {
        while(1) {
            printf("MyRunn3 start \n");
            poll(NULL, 0, 200);
        }
    }
};

int main(void) {
    printf("main thread start \n");
    ArrayList<Filament> list = createArrayList<Filament>();
    Filament f1 = createFilament(createMyRun1());
    Filament f2 = createFilament(createMyRun2());
    Filament f3 = createFilament(createMyRun3());
    list->add(f1);
    list->add(f2);
    list->add(f3);
    
    FilaCroutine croutine = createFilaCroutine(list);
    croutine->start();
    printf("main thread trace1 \n");
    while(1){sleep(100);}
}
