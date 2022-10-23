#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <gtest/gtest.h>
#include <ctime>

#include "lib/decoder.h"
#include "lib/encoder.h"

std::vector<size_t> getTable(std::string str) {
    std::vector<size_t> table(256, 0);
    for (size_t i = 0; i < str.length(); ++i) {
        table[(unsigned char)str[i]]++;
    }
    return table;
}

TEST(correctness, simple)
{
    std::string str = "Simple string to encode";
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, some)
{
    std::string str = "^[[?62;c^[[?62;c^[[?62;c";
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, one_symbol)
{
    std::string str = "a";
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, empty) {
    std::string str = "";
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, some2_2_2_2) {
    std::string str = "SSaaBBqq";
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, some_1_256) {
    std::string str = "";
    for (int i = 0; i <= 255; ++i) {
        str += (unsigned char)i;
    }
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, some_2_256) {
    std::string str = "";
    for (int i = 0; i <= 255; ++i) {
        str += (unsigned char)i;
    }
    for (int i = 0; i <= 255; ++i) {
        str += (unsigned char)i;
    }
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, some_rand_256) {
    std::string str = "";
    for (int i = 0; i <= 255; ++i) {
        for (size_t i = 0; i < (unsigned)(rand() % 100000); ++i) {
            str += (unsigned char)i;
        }
    }
    std::vector<char> a(str.begin(), str.end());
    std::vector<size_t> table = getTable(str);

    encoder en(table);
    decoder de(table);

    EXPECT_EQ(de.decode(en.encode(a)), a);
}

TEST(correctness, randomized_strings) {
    srand(time(0));
    //10^12 total
    const size_t first = 10000;
    const size_t second = 100000000;
    for (size_t i = 0; i < first; ++i) {
        std::string str = "";
        for (size_t j = 0; j < ((unsigned)(rand() % second)); ++j) {
            str += ((unsigned char)(rand() % 256));
        }
        std::vector<char> a(str.begin(), str.end());
        std::vector<size_t> table = getTable(str);

        encoder en(table);
        decoder de(table);

        EXPECT_EQ(de.decode(en.encode(a)), a);
    }
}
