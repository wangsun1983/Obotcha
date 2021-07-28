#include <stdio.h>

#include "MemoryFileInputStream.hpp"
#include "FileNotFoundException.hpp"

using namespace obotcha;

ByteArray testData;

void init() {
    testData = createByteArray(18);
    testData->fill(0,'a');
    testData->fill(1,'a');
    testData->fill(2,'c');
    testData->fill(3,'d');
    testData->fill(4,'e');
    testData->fill(5,'f');
    testData->fill(6,'g');
    testData->fill(7,'h');
    testData->fill(8,'i');
    testData->fill(9,'j');
    testData->fill(10,'k');
    testData->fill(11,'l');
    testData->fill(12,'m');
    testData->fill(13,'n');
    testData->fill(14,'o');
    testData->fill(15,'p');
    testData->fill(16,'e');
    testData->fill(17,'\n');
}

bool compare(int start,int length,ByteArray arr) {
    int index = 0;
    for(;index < length;index++) {
        if(testData->at(index + start) != arr->at(index)) {
            printf("testData[%d] is %x,arr[%d] is %x \n",index + start,testData->at(index + start),index,arr->at(index));
            return false;
        }
    }

    return true;
}

int main() {
    printf("---[MemoryFileInputStream Test Start]--- \n");
    init();

    //bool open();
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        if(!input->open()) {
            printf("---[MemoryFileInputStream Test {open()} case1] [FAIL]--- \n");
            break;
        }

        input->close();

        input = createMemoryFileInputStream(createString("abc.file"));
        if(input->open()) {
            printf("---[MemoryFileInputStream Test {open()} case2] [FAIL]--- \n");
            break;
        }

        input->close();

        printf("---[MemoryFileInputStream Test {open()} case3] [Success]--- \n");
        break;
    }

    //int read();
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        if(input->open()) {
            int value = input->read();
            if(value != 'a') {
                printf("---[MemoryFileInputStream Test {read()} case1] [FAIL]--- \n");
                break;
            } 
        } else {
            printf("---[MemoryFileInputStream Test {read()} case2] [FAIL]--- \n");
            break;
        }

        MemoryFileInputStream input2 = createMemoryFileInputStream(createString("abc.file"));
        input2->open();
        bool isException = false;
        try {
            int value = input2->read();
        } catch(FileNotFoundException e) {
            isException = true;
        }
        
        if(!isException) {
            printf("---[MemoryFileInputStream Test {read()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {read()} case4] [Success]--- \n");
        break;
    }
    
    //int read(ByteArray buffer);
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        if(input->open()) {
            ByteArray array = createByteArray(6);
            int length = input->read(array);
            if(length != 6) {
                printf("---[MemoryFileInputStream Test {read(ByteArray)} case1] [FAIL]--- \n");
            }

            if(!compare(0,length,array)) {
                printf("---[MemoryFileInputStream Test {read(ByteArray)} case2] [FAIL]--- \n");
            }

            ByteArray array2 = createByteArray(64);
            length = input->read(array2);

            if(length != 18) {
                printf("---[MemoryFileInputStream Test {read(ByteArray)} case3] [FAIL]---\n");
            }

            if(!compare(0,length,array2)) {
                printf("---[MemoryFileInputStream Test {read(ByteArray)} case4] [FAIL]--- \n");
            }

            break;
        } else {
            printf("---[MemoryFileInputStream Test {read(ByteArray)} case3] [FAIL]--- \n");
            break;
        }

        input = createMemoryFileInputStream(createString("abc.file"));
        ByteArray array = createByteArray(6);
        int size = input->read(array);
        if(size != -1) {
            printf("---[MemoryFileInputStream Test {read(ByteArray)} case4] [FAIL]---\n");
            break;
        }

        printf("---[MemoryFileInputStream Test {read(ByteArray)} case5] [Success]--- \n");
        break;
    }

    //int read(int index,ByteArray buffer);
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        if(input->open()) {
            ByteArray array = createByteArray(6);
            int length = input->read(2,array);
            if(length != 6) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case1] [FAIL]---\n");
                break;
            }

            if(!compare(2,length,array)) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case2] [FAIL]--- \n");
                break;
            }

            ByteArray array2 = createByteArray(64);
            length = input->read(2,array2);
            if(length != 16) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case3] [FAIL]---\n");
                break;
            }

            if(!compare(2,length,array2)) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case3] [FAIL]--- \n");
                break;
            }
            
            printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case4] [Success]---\n");
            break;

            ByteArray array3 = createByteArray(64);
            int length3 = input->read(64,array3);
            if(length3 != -1) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case5] [FAIL]--- \n");
                break;
            }
        }

        MemoryFileInputStream input4 = createMemoryFileInputStream(createString("abc.file"));
        ByteArray array4 = createByteArray(64);
        int length4 = input->read(1,array4);
        if(length4 != -1) {
            printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case6] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case6] [Success]--- \n");
        break;
    }

    //ByteArray readAll();
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        if(input->open()) {
            ByteArray array = input->readAll();
            if(array->size() != 18) {
                printf("---[MemoryFileInputStream Test {readAll()} case1] [FAIL]--- \n");
                break;
            }
        
            if(!compare(0,array->size(),array)) {
                printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case3] [FAIL]--- \n");
                break;
            }
        }

        input = createMemoryFileInputStream(createString("abc.file"));
        input->open();
        ByteArray array2 = input->readAll();
        if(array2 != nullptr) {
            printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case4] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {read(int,ByteArray)} case5] [Success]--- \n");
        break;
    }


    //void close();
    while(1) {
        MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
        input->close();

        printf("---[MemoryFileInputStream Test {close()} case1] [Success]--- \n");
        break;
    }
    
}
