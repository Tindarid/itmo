#include "counted.h"
#include <gtest/gtest.h>
#include "fault_injection.h"

counted::counted(int data)
    : data(data)
{
    auto p = instances.insert(this);
    if (!p.second)
    {
        fault_injection_disable dg;
        ADD_FAILURE() << "constructor call on already existing object";
    }
}

counted::counted(counted const& other)
    : data(other.data)
{
    auto p = instances.insert(this);
    if (!p.second)
    {
        fault_injection_disable dg;
        ADD_FAILURE() << "constructor call on already existing object";
    }
}

counted::~counted()
{
    fault_injection_disable dg;
    size_t n = instances.erase(this);
    if (n != 1u)
        ADD_FAILURE() << "destructor call on non-existing object";
}

counted& counted::operator=(counted const& c)
{
    if (instances.find(this) == instances.end())
        ADD_FAILURE() << "assignment operator call on non-existing object";

    data = c.data;
    return *this;
}

counted::operator int() const
{
    if (instances.find(this) == instances.end())
        ADD_FAILURE() << "accessing non-existing object";

    return data;
}

bool operator==(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data == b.data;
}

bool operator!=(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data != b.data;
}

bool operator<(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data < b.data;
}

bool operator<=(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data <= b.data;
}

bool operator>(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data > b.data;
}

bool operator>=(counted const& a, counted const& b)
{
    fault_injection_point();
    return a.data >= b.data;
}

bool operator==(counted const& a, int b)
{
    fault_injection_point();
    return a.data == b;
}

bool operator!=(counted const& a, int b)
{
    fault_injection_point();
    return a.data != b;
}

bool operator<(counted const& a, int b)
{
    fault_injection_point();
    return a.data < b;
}

bool operator<=(counted const& a, int b)
{
    fault_injection_point();
    return a.data <= b;
}

bool operator>(counted const& a, int b)
{
    fault_injection_point();
    return a.data > b;
}

bool operator>=(counted const& a, int b)
{
    fault_injection_point();
    return a.data >= b;
}


bool operator==(int a, counted const& b)
{
    fault_injection_point();
    return a == b.data;
}

bool operator!=(int a, counted const& b)
{
    fault_injection_point();
    return a != b.data;
}

bool operator<(int a, counted const& b)
{
    fault_injection_point();
    return a < b.data;
}

bool operator<=(int a, counted const& b)
{
    fault_injection_point();
    return a <= b.data;
}

bool operator>(int a, counted const& b)
{
    fault_injection_point();
    return a > b.data;
}

bool operator>=(int a, counted const& b)
{
    fault_injection_point();
    return a >= b.data;
}

std::set<counted const*> counted::instances;

counted::no_new_instances_guard::no_new_instances_guard()
    : old_instances(instances)
{}

counted::no_new_instances_guard::~no_new_instances_guard()
{
    EXPECT_TRUE(old_instances == instances);
}

void counted::no_new_instances_guard::expect_no_instances()
{
    EXPECT_TRUE(old_instances == instances);
}
