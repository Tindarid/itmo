#include <iostream>
#include <cstring>
#include <sys/mman.h>

using std::memcpy;

const size_t FUNC_SIZE = 55;
const size_t OPERAND_SIZE = 4;
const uint64_t INITIAL = 7;
const uint64_t DEDUCE = 14;
const int RANGE = 1000;
const uint8_t FUNC[] = {
    0x55,                                     //push   %rbp
    0x48, 0x89, 0xe5,             	          //mov    %rsp,%rbp
    0xc7, 0x45, 0xf8, 0x2a, 0x00, 0x00, 0x00, //movl   $0x2a,-0x8(%rbp)
    0xc7, 0x45, 0xfc, 0x54, 0x00, 0x00, 0x00, //movl   $0x54,-0x4(%rbp)
    0x8b, 0x45, 0xf8,             	          //mov    -0x8(%rbp),%eax
    0x3b, 0x45, 0xfc,             	          //cmp    -0x4(%rbp),%eax
    0x7e, 0x07,           	                  //jle    113a <_Z4funcv+0x21>
    0xb8, 0x01, 0x00, 0x00, 0x00,       	  //mov    $0x1,%eax
    0xeb, 0x14,                               //jmp    114e <_Z4funcv+0x35>
    0x8b, 0x45, 0xf8,             	          //mov    -0x8(%rbp),%eax
    0x3b, 0x45, 0xfc,             	          //cmp    -0x4(%rbp),%eax
    0x7d, 0x07,                	              //jge    1149 <_Z4funcv+0x30>
    0xb8, 0x02, 0x00, 0x00, 0x00,      	      //mov    $0x2,%eax
    0xeb, 0x05,                	              //jmp    114e <_Z4funcv+0x35>
    0xb8, 0x00, 0x00, 0x00, 0x00,       	  //mov    $0x0,%eax
    0x5d,                  	                  //pop    %rbp
    0xc3                   	                  //retq   
};

void finish() {
    perror("");
    exit(EXIT_FAILURE);
}

uint64_t getRandom() {
    srand(time(0));
    return rand() % RANGE + 1;
}

void* init() {
    void *addr = mmap(NULL, FUNC_SIZE, PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == (void*) -1) {
        finish();
    }
    memcpy(reinterpret_cast<uint8_t*>(addr), FUNC, FUNC_SIZE);
    return addr;
}

void setOperand(void* addr, uint64_t op, size_t pos) {
    if (mprotect(addr, FUNC_SIZE, PROT_WRITE) == -1) {
        finish();
    }
    memcpy(reinterpret_cast<uint8_t*>(addr) + pos, &op, OPERAND_SIZE);
    if (mprotect(addr, FUNC_SIZE, PROT_READ | PROT_EXEC) == -1) {
        finish();
    }
}

int main() {
    uint64_t numberToDeduce = getRandom();
    void* addr = init();

    setOperand(addr, numberToDeduce, INITIAL);

    int (*fcnPtr)() = reinterpret_cast<int(*)()>(addr);

    printf("Try to guess my number\nIt is in range [1;1000]\nPrint '0' to exit\n");
    while (true) {
        uint64_t a;
        std::cin >> a;
        if (a == 0) {
            printf("My number was: %d\n", numberToDeduce);
            break;
        }
        if (a > RANGE || a < 1) {
            printf("Too big number\n");
            continue;
        }
        setOperand(addr, a, DEDUCE);
        int result = fcnPtr();
        if (result == 1) {
            printf("Smaller then mine\n");
        } else if (result == 2) {
            printf("Greater then mine\n");
        } else {
            printf("Correct\n");
            break;
        }
    }
    if (munmap(addr, FUNC_SIZE) == -1) {
        finish();
    }
    exit(EXIT_SUCCESS);
}
