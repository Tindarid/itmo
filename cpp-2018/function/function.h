#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>
#include <cstring>
#define FUNCTION_BUF_SIZE 64

namespace my {
    template<typename>
    class function;

    template<typename R, typename ...Args>
    class function<R(Args...)> {
    private:
        class functor {
        public:
            virtual ~functor() {};
            virtual R result(Args&&...) = 0;
            virtual std::unique_ptr<functor> copy() const = 0;
        };

        template<typename T>
        class functor_impl : public functor {
        public:
            functor_impl(T&& t) : t(std::move(t)) {}
            functor_impl(const T& t) : t(t) {}
            ~functor_impl() override = default;
            R result(Args&&... args) override {
                return t(std::forward<Args>(args)...);
            }
            std::unique_ptr<functor> copy() const override {
                return std::make_unique<functor_impl<T>>(t);
            }
        private:
            T t;
        };
        union {
            std::unique_ptr<functor> func;
            char buf[FUNCTION_BUF_SIZE];
        };
        bool small;
    public:
        function() noexcept : func(nullptr), small(false) {}

        template<typename F>
        function(F func) {
            if (sizeof(func) > FUNCTION_BUF_SIZE) {
                this->small = false;
                new (this->buf) std::unique_ptr<functor_impl<F>>(std::make_unique<functor_impl<F>>(std::move(func)));
            } else {
                this->small = true;
                new (this->buf) functor_impl<F>(std::move(func));
            }
        }

        function(std::nullptr_t) noexcept : func(nullptr), small(false) {}

        function(const function& other) {
            if (other.small) {
                this->small = true;
                memcpy(this->buf, other.buf, FUNCTION_BUF_SIZE);
            } else {
                this->small = false;
                func = other.func->copy();
            }
        }

        function(function&& other) noexcept : func(nullptr), small(false) {
            this->swap(other);
        }

        ~function() {
            if (this->small) {
                ((functor*)this->buf)->~functor();
            } else {
                this->func.reset();
            }
        }

        function& operator=(const function& other) {
            auto temp(other);
            this->swap(temp);
            return *this;
        }

        function& operator=(function&& other) noexcept {
            this->swap(other);
            return *this;
        }

        void swap(function& other) noexcept {
            std::swap(this->buf, other.buf);
            std::swap(this->small, other.small);
        }

        explicit operator bool() const noexcept {
            return static_cast<bool>(func);
        }

        R operator()(Args... args) const {
            return small ? ((functor*)(buf))->result(std::forward<Args>(args)...)
                         : func->result(std::forward<Args>(args)...);
        }
    };
}

#endif
