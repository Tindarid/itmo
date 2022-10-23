#include <iostream>
#include <dlfcn.h>

#include "libs/static/factorial.h"
#include "libs/dynamic1/binpow.h"
#include "libs/dynamic2/pow.h"

using std::cout;
using std::endl;

int main() {
    void *lib = dlopen("./libpow.so", RTLD_LAZY | RTLD_GLOBAL);
    if (!lib) {
        cout << "Error while loading pow library. Aborting" << endl;
        cout << dlerror() << endl;
        return 0;
    }

    long long (*pow_count)(int, int) = (long long(*)(int, int))dlsym(lib, "count");
    if (!pow_count) {
        cout << "Error while getting function pointer" << endl;
        cout << dlerror() << endl;
        return 0;
    }

    cout << factorial::count(5) << endl;
    cout << binpow::count(5, 3) << endl;
    cout << pow_count(5, 3) << endl;

    if (dlclose(lib) != 0) {
        cout << "Error while closing pow library" << endl;
    }
    return 0;
}
