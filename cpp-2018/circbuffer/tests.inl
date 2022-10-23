#include <gtest/gtest.h>

#include "fault_injection.h"

/*template <typename T>
T const& as_const(T& obj)
{
    return obj;
}*/
using std::as_const;

template <typename C, typename T>
void mass_push_back(C& c, std::initializer_list<T> elems)
{
    for (T const& e : elems)
        c.push_back(e);
}

template <typename C, typename T>
void mass_push_front(C& c, std::initializer_list<T> elems)
{
    for (T const& e : elems)
        c.push_front(e);
}

template <typename It, typename T>
void expect_eq(It i1, It e1, std::initializer_list<T> elems)
{
    std::vector<typename std::remove_const<typename std::iterator_traits<It>::value_type>::type> vals;

    for (; i1 != e1; ++i1)
        vals.push_back(*i1);

    if (!std::equal(vals.begin(), vals.end(), elems.begin(), elems.end()))
    {
        std::stringstream ss;
        ss << '{';

        bool add_comma = false;
        for (auto const& e : vals)
        {
            if (add_comma)
                ss << ", ";
            ss << e;
            add_comma = true;
        }

        ss << "} != {";

        add_comma = false;
        for (auto const& e : elems)
        {
            if (add_comma)
                ss << ", ";
            ss << e;
            add_comma = true;
        }

        ss << "}";

        ADD_FAILURE() << ss.str();
    }
}

template <typename C, typename T>
void expect_eq(C const& c, std::initializer_list<T> elems)
{
    expect_eq(c.begin(), c.end(), elems);
}

template <typename C, typename T>
void expect_reverse_eq(C const& c, std::initializer_list<T> elems)
{
    expect_eq(c.rbegin(), c.rend(), elems);
}

TEST(correctness, push_back)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    expect_eq(c, {1, 2, 3, 4});
}

TEST(correctness, back_front)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});
    EXPECT_EQ(1, c.front());
    EXPECT_EQ(1, as_const(c).front());
    EXPECT_EQ(5, c.back());
    EXPECT_EQ(5, as_const(c).back());
}

TEST(correctness, copy_ctor)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container c2 = c;
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, copy_ctor_2)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_front(c, {1, 2, 3, 4, 5});
    container c2 = c;
    expect_eq(c2, {5, 4, 3, 2, 1});
}

TEST(correctness, copy_ctor_empty)
{
    counted::no_new_instances_guard g;

    container c;
    container c2 = c;
    EXPECT_TRUE(c2.empty());
}

TEST(correctness, assignment_operator)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container c2;
    mass_push_back(c2, {5, 6, 7, 8});
    c2 = c;
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, self_assignment)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c = c;
    expect_eq(c, {1, 2, 3, 4});
}

TEST(correctness, pop_back)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.pop_back();
    expect_eq(c, {1, 2, 3});
    c.pop_back();
    expect_eq(c, {1, 2});
    c.pop_back();
    expect_eq(c, {1});
    c.pop_back();
    EXPECT_TRUE(c.empty());
}

TEST(correctness, push_front)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_front(c, {1, 2, 3, 4});
    expect_eq(c, {4, 3, 2, 1});
}

TEST(correctness, empty)
{
    counted::no_new_instances_guard g;

    container c;
    EXPECT_EQ(c.begin(), c.end());
    EXPECT_TRUE(c.empty());
    c.push_back(1);
    EXPECT_NE(c.begin(), c.end());
    EXPECT_FALSE(c.empty());
    c.pop_front();
    EXPECT_EQ(c.begin(), c.end());
    EXPECT_TRUE(c.empty());
}

TEST(correctness, queue)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});

    for (int i = 6; i != 100; ++i)
    {
        c.push_back(i);
        c.pop_front();
    }
    
    expect_eq(c, {95, 96, 97, 98, 99});
}

TEST(correctness, bogus_queue)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});

    for (int i = 6; i != 100; ++i)
    {
        c.push_back(i);
        c.erase(c.begin() + 1);
    }
    
    expect_eq(c, {1, 96, 97, 98, 99});
}

TEST(correctness, reverse_iterators)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_front(c, {1, 2, 3, 4});
    expect_reverse_eq(c, {1, 2, 3, 4});
    
    EXPECT_EQ(1, *c.rbegin());
    EXPECT_EQ(2, *std::next(c.rbegin()));
    EXPECT_EQ(4, *std::prev(c.rend()));
}

TEST(correctness, iterator_conversions)
{
    counted::no_new_instances_guard g;

    container c;
    container::const_iterator i1 = c.begin();
    container::iterator i2 = c.end();
    EXPECT_TRUE(i1 == i1);
    EXPECT_TRUE(i1 == i2);
    EXPECT_TRUE(i2 == i1);
    EXPECT_TRUE(i2 == i2);
    EXPECT_FALSE(i1 != i1);
    EXPECT_FALSE(i1 != i2);
    EXPECT_FALSE(i2 != i1);
    EXPECT_FALSE(i2 != i2);
}

TEST(correctness, iterators_postfix)
{
    counted::no_new_instances_guard g;

    container s;
    mass_push_back(s, {1, 2, 3});
    container::iterator i = s.begin();
    EXPECT_EQ(1, *i);
    container::iterator j = i++;
    EXPECT_EQ(2, *i);
    EXPECT_EQ(1, *j);
    j = i++;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(2, *j);
    j = i++;
    EXPECT_EQ(s.end(), i);
    EXPECT_EQ(3, *j);
    j = i--;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(s.end(), j);
}

TEST(correctness, insert_empty)
{
    counted::no_new_instances_guard g;

    container c;
    c.insert(c.begin(), 5);
    mass_push_back(c, {4, 3, 2, 1});
    expect_eq(c, {5, 4, 3, 2, 1});
}

TEST(correctness, insert_begin)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(c.begin(), 0);
    expect_eq(c, {0, 1, 2, 3, 4});
}

TEST(correctness, insert_middle)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(std::next(c.begin(), 2), 5);
    expect_eq(c, {1, 2, 5, 3, 4});
}

TEST(correctness, insert_close_to_end)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5, 6});
    c.insert(std::next(c.begin(), 4), 42);
    expect_eq(c, {1, 2, 3, 4, 42, 5, 6});
}

TEST(correctness, insert_end)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(c.end(), 5);
    expect_eq(c, {1, 2, 3, 4, 5});
}

TEST(correctness, erase_begin)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(c.begin());
    expect_eq(c, {2, 3, 4});
}

TEST(correctness, erase_middle)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::next(c.begin(), 2));
    expect_eq(c, {1, 2, 4});
}

TEST(correctness, erase_close_to_end)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5, 6});
    c.erase(std::next(c.begin(), 4));
    expect_eq(c, {1, 2, 3, 4, 6});
}

TEST(correctness, erase_end)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::prev(c.end()));
    expect_eq(c, {1, 2, 3});
}

TEST(correctness, subscript)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(c.begin() + 2);
    c.pop_front();
    EXPECT_EQ(2, c[0]);
    EXPECT_EQ(4, c[1]);
    EXPECT_EQ(2, as_const(c)[0]);
    EXPECT_EQ(4, as_const(c)[1]);
}

TEST(correctness, size)
{
    counted::no_new_instances_guard g;

    container c;
    for (size_t i = 0; i != 10; ++i)
    {
        EXPECT_EQ(i, c.size());
        c.push_back(42);
    }
    EXPECT_EQ(10u, c.size());
}

TEST(correctness, clear)
{
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(6u, c.size());
    c.clear();
    EXPECT_EQ(0u, c.size());
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(c.end(), c.begin());
}

TEST(correctness, swap)
{
    counted::no_new_instances_guard g;

    container c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    mass_push_back(c2, {5, 6, 7, 8});
    swap(c1, c2);
    expect_eq(c1, {5, 6, 7, 8});
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, swap_self)
{
    counted::no_new_instances_guard g;

    container c1;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c1);
}

TEST(correctness, swap_empty)
{
    counted::no_new_instances_guard g;

    container c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c2);
    EXPECT_TRUE(c1.empty());
    expect_eq(c2, {1, 2, 3, 4});
    swap(c1, c2);
    expect_eq(c1, {1, 2, 3, 4});
    EXPECT_TRUE(c2.empty());
}

TEST(correctness, swap_empty_empty)
{
    counted::no_new_instances_guard g;

    container c1, c2;
    swap(c1, c2);
}

TEST(correctness, swap_empty_self)
{
    counted::no_new_instances_guard g;

    container c1;
    swap(c1, c1);
}


TEST(correctness, swap_iterator_validity)
{
    counted::no_new_instances_guard g;

    container c1, c2;
    mass_push_back(c1, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    c2.push_back(11);
    
    container::const_iterator c1_begin = c1.begin();
    container::const_iterator c1_end = c1.end();

    container::const_iterator c2_begin = c2.begin();
    container::const_iterator c2_end = c2.end();

    swap(c1, c2);

    EXPECT_EQ(1, *c1_begin++);
    EXPECT_EQ(2, *c1_begin++);
    EXPECT_EQ(3, *c1_begin++);
    c1_begin += 7;
    EXPECT_EQ(c1_end, c1_begin);
    
    EXPECT_EQ(11, *c2_begin++);
    EXPECT_EQ(c2_end, c2_begin);
}


TEST(fault_injection, non_throwing_default_ctor)
{
    faulty_run([]
    {
        try
        {
            container();
        }
        catch (...)
        {
            fault_injection_disable dg;
            ADD_FAILURE() << "default constructor throws";
            throw;
        }
    });
}

TEST(fault_injection, push_back_1)
{
    faulty_run([]
    {
        container c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(3);
        fault_injection_disable dg;
        expect_eq(c, {1, 2, 3});
    });
}

TEST(fault_injection, copy_ctor)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        container c2 = c;
        fault_injection_disable dg;
        expect_eq(c, {1, 2, 3, 4});
        expect_eq(c2, {1, 2, 3, 4});
    });
}

TEST(fault_injection, non_throwing_clear)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        try
        {
            c.clear();
        }
        catch (...)
        {
            fault_injection_disable dg;
            ADD_FAILURE() << "clear throws";
            throw;
        }
    });
}

TEST(fault_injection, assignment_operator)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        container c2;
        mass_push_back(c2, {5, 6, 7, 8});
        
        try
        {
            c = c2;
        }
        catch (...)
        {
            fault_injection_disable dg;
            expect_eq(c, {1, 2, 3, 4});
            throw;
        }
        
        fault_injection_disable dg;
        expect_eq(c, {5, 6, 7, 8});
    });
}

TEST(fault_injection, push_back_2)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        
        try
        {
            c.push_back(5);
        }
        catch (...)
        {
            fault_injection_disable dg;
            expect_eq(c, {1, 2, 3, 4});
            throw;
        }
        
        fault_injection_disable dg;
        expect_eq(c, {1, 2, 3, 4, 5});
    });
}

TEST(fault_injection, push_front)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        
        try
        {
            c.push_front(5);
        }
        catch (...)
        {
            fault_injection_disable dg;
            expect_eq(c, {1, 2, 3, 4});
            throw;
        }
        
        fault_injection_disable dg;
        expect_eq(c, {5, 1, 2, 3, 4});
    });
}

TEST(fault_injection, insert)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {1, 2, 3, 4});
        
        c.insert(c.begin() + 2, 5);

        fault_injection_disable dg;
        expect_eq(c, {1, 2, 5, 3, 4});
    });
}

TEST(fault_injection, erase)
{
    faulty_run([]
    {
        container c;
        mass_push_back(c, {6, 3, 8, 2, 5, 7, 10});
    
        c.erase(c.begin() + 4);

        fault_injection_disable dg;
        expect_eq(c, {6, 3, 8, 2, 7, 10});
    });
}
