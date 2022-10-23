#ifndef TUPLE_H
#define TUPLE_H

#include <type_traits>
#include <utility>

namespace tuple_namespace {
    template<typename Head, typename ...Tail>
    class tuple {
        public:
            tuple() : head(), tail() {}

            template<typename H, typename ...T>
            tuple(H&& h, T&&... t) : head(std::forward<H>(h)), tail(std::forward<T>(t)...) {}
            Head head;
            tuple<Tail...> tail;
    };

    template<typename Head>
    class tuple<Head> {
        public:
            tuple() : head() {}

            template<typename H>
            tuple(H&& h) : head(std::forward<H>(h)) {}
            Head head;
    };

    template<typename T, typename Head, typename ...Tail>
    struct is_in {
        static constexpr bool value = std::conditional_t<is_in<T, Head>::value || is_in<T, Tail...>::value,
                      std::true_type, std::false_type>::value;
    };

    template<typename T, typename V>
    struct is_in<T, V> : std::is_same<T, V> { };

    template<typename T, typename Head, typename ...Tail>
    typename std::enable_if_t<!is_in<T, Head>::value && is_in<T, Tail...>::value, T>
             get(tuple<Head, Tail...> const& tup) {
        return get<T>(tup.tail);
    }

    template<typename T, typename Head, typename ...Tail>
    typename std::enable_if_t<is_in<T, Head>::value && !is_in<T, Tail...>::value, T>
             get(tuple<Head, Tail...> const& tup) {
        return tup.head;
    }

    template<typename T, typename Head>
    typename std::enable_if_t<is_in<T, Head>::value, T>
             get(tuple<Head> const& tup) {
        return tup.head;
    }

    template<int index, typename Head, typename ...Tail>
    auto get(tuple<Head, Tail...> const& tup) ->
         typename std::enable_if_t<(index > 0), decltype(get<index - 1, Tail...>(tup.tail))> {
        return get<index - 1>(tup.tail);
    }

    template<int index, typename Head, typename ...Tail>
    typename std::enable_if_t<(index == 0), Head>
             get(tuple<Head, Tail...> const& tup) {
        return tup.head;
    }

    /*
    template<int index, typename Head>
    typename std::enable_if_t<(index == 0), Head> get(tuple<Head> const& tup) {
        return tup.head;
    }
    */
}
#endif
