#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>

#include <signal.h>
#include <unistd.h>

#include <vector>

#define SIZE 16

void abort(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void write_char(uint8_t k) {
    write(1, &k, 1);
}

void write_nibble(uint8_t k) {
    char c = k < 10 ? k + '0' : k + 'A' - 10;
    write(1, &c, 1);
}

void write_byte(uint8_t k) {
    write_nibble(k / 16);
    write_nibble(k % 16);
}

void write_string(const char *s) {
    write(1, s, strlen(s));
}

void write_qword(uint64_t value) {
    for (int i = 8; i >= 1; --i) {
        write_byte(0xFF & (value >> (8 * (i - 1))));
    }   
}

void action(int sig, siginfo_t* info, void* context) {
    struct ucontext_t* p = (ucontext_t*)context;
    std::vector<std::pair<const char*, uint64_t>> registers = {
        {"R8      ", REG_R8},
        {"R9      ", REG_R9},
        {"R10     ", REG_R10},
        {"R11     ", REG_R11},
        {"R12     ", REG_R12},
        {"R13     ", REG_R13},
        {"R14     ", REG_R14},
        {"R15     ", REG_R15},
        {"RDI     ", REG_RDI},
        {"RSI     ", REG_RSI},
        {"RBP     ", REG_RBP},
        {"RSP     ", REG_RSP},
        {"RAX     ", REG_RAX},
        {"RBX     ", REG_RBX},
        {"RCX     ", REG_RCX},
        {"RDX     ", REG_RDX},
        {"RIP     ", REG_RIP},
        {"EFL     ", REG_EFL},
        {"CSGSFS  ", REG_CSGSFS},
        {"ERR     ", REG_ERR},
        {"TRAPNO  ", REG_TRAPNO},
        {"OLDMASK ", REG_OLDMASK},
        {"CR2     ", REG_CR2}
    };
    for (auto reg : registers) {
        write_string(reg.first);
        write_qword(p->uc_mcontext.gregs[reg.second]);
        write_string("\n");
    }

    /* Memory dump inspired by https://vxlab.info/wasm/article.php-article=1022001.htm */
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        abort("Cannot make pipe");
    }
    for (int i = -(SIZE / 2); i < SIZE / 2; ++i) {
        write_qword((uint64_t)((char*)(info->si_addr) + i * SIZE));
        write_string(" ");
        for (int j = i * SIZE; j < (i + 1) * SIZE; ++j) {
            char *a = (char*)(info->si_addr) + j;
            uint8_t value;
            if (write(pipefd[1], a, 1) == -1) {
                write_string("??");
            } else if (read(pipefd[0], &value, 1) == -1) {
                write_string("??");
            } else {
                write_byte(value);
            }
            write_string(" ");
        }
        for (int j = i * SIZE; j < (i + 1) * SIZE; ++j) {
            char *a = (char*)(info->si_addr) + j;
            uint8_t value;
            if (write(pipefd[1], a, 1) == -1) {
                value = '.';
            } else if (read(pipefd[0], &value, 1) == -1 || value < 33 || value > 127) {
                value = '.';
            }
            write_char(value);
        }
        write_string("\n");
    }
    exit(EXIT_SUCCESS);
}

const char hello[] = "Hello world";

int main() {
    struct sigaction sigact;
    sigact.sa_flags = SA_SIGINFO;
    if (sigemptyset(&sigact.sa_mask) == -1) {
        abort("Cannot make set of signals");
    }
    sigact.sa_sigaction = action;
    if (sigaction(SIGSEGV, &sigact, NULL) == -1) {
        abort("Cannot do sigaction");
    }

    /* Test section */
    /* Test 1 */
    /*
    int* test1 = reinterpret_cast<int*>(main);
    *test1 = 0;
    */

    /*Test 2*/
    /*
    char* test2 = const_cast<char*>(hello);
    *test2 = 0;
    */

    exit(EXIT_SUCCESS);
}
