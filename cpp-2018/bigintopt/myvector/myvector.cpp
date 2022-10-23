#include "myvector.h"
#include <algorithm>

typedef unsigned int UI;

myvector::myvector() {
    _capacity = _size = 0;
}

myvector::myvector(myvector const& other) {
    copyVector(*this, other);
}

myvector::~myvector() {
    if (is_big()) {
        --_data.big->count;
        if (_data.big->count == 0 && _capacity > 0) {
            /*
            delete[] _data.big->data;
            */
            delete _data.big;
        }
   }
}

void myvector::detach() {
    if (!is_big() || _data.big->count == 1) {
        return;
    }
    arrholder *temp = static_cast<arrholder*>(operator new(sizeof(arrholder) + sizeof(UI) * _capacity));
    /*
    arrholder* temp = new arrholder;
    temp->data = new UI[_capacity];
    */
    for (size_t i = 0; i < _capacity; ++i) {
        temp->data[i] = _data.big->data[i];
    }
    temp->count = 1;
    --_data.big->count;
    _data.big = temp;
}

void myvector::ensureCapacity(size_t newcap) {
    if (newcap < _capacity) {
        return;
    }
    UI temp = _size;
    resize((std::max(_capacity, _size) + 1) * 2);
    _size = temp;
}

void myvector::copyVector(myvector &a, myvector const& b) {
    a._capacity = b._capacity;
    a._size = b._size;
    a._data = b._data;
    if (b.is_big()) {
        _data.big->count++;
    }
}

myvector& myvector::operator=(myvector const& other) {
    if (is_big()) {
        _data.big->count--;
        if (_data.big->count == 0) {
            /*
            delete[] _data.big->data;
            */
            delete _data.big;
        }
    }
    copyVector(*this, other);
    return *this;
}

void myvector::resize(size_t newcap) {
    detach();
    if (newcap == 0) {
        if (is_big()) {
            /*
            delete[] _data.big->data;
            */
            delete _data.big;
        }
        _size = _capacity = 0;
    } else if (newcap == 1) {
        if (is_big()) {
            UI temp = _data.big->data[0];
            /*
            delete[] _data.big->data;
            */
            delete _data.big;
            _data.small = temp;
        }
        _capacity = 0;
        _size = 1;
    } else {
        if (is_big()) {
            /*
            UI* temp = new UI[newcap];
            for (size_t i = 0; i < std::min(_size, newcap); ++i) {
                temp[i] = _data.big->data[i];
            }
            delete[] _data.big->data;
            _data.big->data = temp;
            _size = _capacity = newcap;
            */
            arrholder* temp = static_cast<arrholder*>(operator new(sizeof(arrholder) + sizeof(UI) * newcap));
            temp->count = _data.big->count;
            for (size_t i = 0; i < std::min(_size, newcap); ++i) {
                temp->data[i] = _data.big->data[i];
            }
            delete _data.big;
            _data.big = temp;
            _size = _capacity = newcap;
        } else {
            UI temp = 0;
            if (_size == 1) {
                temp = _data.small;
            }
            /*
            _data.big = new arrholder;
            _data.big->data = new UI[newcap];
            */
            _data.big = static_cast<arrholder*>(operator new(sizeof(arrholder) + sizeof(UI) * newcap));
            for (size_t i = 0; i < newcap; ++i) {
                _data.big->data[i] = 0;
            }
            _data.big->count = 1;
            _data.big->data[0] = temp;
            _size = _capacity = newcap;
        }
    }
}

void myvector::clear() {
    if (is_big()) {
        --_data.big->count;
        if (_data.big->count <= 1) {
            /*
            delete[] _data.big->data;
            */
            delete _data.big;
        }
    }
    _size = _capacity = 0;
}

void myvector::push_back(UI a) {
    if (!is_big()) {
        if (_size == 0) {
            _data.small = a;
            _size = 1;
            _capacity = 0;
        } else {
            _size = 2;
            _capacity = 2;
            UI temp = _data.small;
            _data.big = static_cast<arrholder*>(operator new(sizeof(arrholder) + sizeof(UI) * 2));
            /*
            _data.big = new arrholder;
            _data.big->data = new UI[2];
            */
            _data.big->count = 1;
            _data.big->data[0] = temp;
            _data.big->data[1] = a;
        }
        return;
    }
    detach();
    ensureCapacity(_size + 1);
    _data.big->data[_size] = a;
    ++_size;
}

void myvector::pop_back() {
    --_size;
    if (_size == 1) {
        UI temp = _data.big->data[0];
        /*
        delete[] _data.big->data;
        */
        delete _data.big;
        _data.small = temp;
        _capacity = 0;
    }
}

UI myvector::operator[](size_t index) const {
    return (is_big() ? _data.big->data[index] : _data.small);
}

UI& myvector::operator[](size_t index) {
    detach();
    return (is_big() ? _data.big->data[index] : _data.small);
}

UI myvector::back() const {
    return (is_big() ? _data.big->data[_size - 1] : _data.small);
}

size_t myvector::size() const {
    return _size;
}

bool myvector::is_big() const {
    return (_capacity == 0 ? false : true);
}
