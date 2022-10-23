#ifndef MY_VECTOR_H
#define MY_VECTOR_H
#include <cstddef>

struct arrholder {
    int count;
    unsigned int data[];
};

class myvector {
    public:
        myvector();
        myvector(myvector const& other);
        ~myvector();

        size_t size() const;
        unsigned int back() const;
        void resize(size_t newcap);
        void clear();
        void push_back(unsigned int a);
        void pop_back();

        unsigned int& operator[](size_t index);
        unsigned int operator[](size_t index) const;
        myvector& operator=(myvector const& other);

    private:
        void detach();
        void ensureCapacity(size_t newcap);
        bool is_big() const;
        void copyVector(myvector &a, myvector const& b);
        size_t _capacity;
        size_t _size;
        union {
            arrholder* big;
            unsigned int small;
        } _data;
};
#endif
