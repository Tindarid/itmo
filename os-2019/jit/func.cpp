int func() {
    int a = 42;
    int b = 84;
    if (a > b) {
        return 1;
    }
    if (a < b) {
        return 2;
    }
    return 0;
}

int main() {
    func();
}
