#include <gtest/gtest.h>

#include "Variant.h"

#include <list>
#include <ostream>
#include <set>
#include <string>
#include <vector>

TEST(Variant, DefaultConstructor)
{
    Variant variant1;
    EXPECT_TRUE(variant1.isNull());
}

TEST(Variant, CopyConstructor)
{
    Variant variant1;
    
    Variant variant2(variant1);
    EXPECT_TRUE(variant2.isNull());
    
    Variant variant3;
    variant3.set<int>(1);
    
    Variant variant4(variant3);
    EXPECT_TRUE(!variant4.isNull());
    EXPECT_EQ(variant4.get<int>(), 1);
    
    variant3.reset();
    EXPECT_TRUE(!variant4.isNull());
}

TEST(Variant, ValueConstructor)
{
    Variant variant1(2);
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 2);
    
    Variant variant2(3);
    EXPECT_TRUE(!variant2.isNull());
    EXPECT_EQ(variant2.get<int>(), 3);
    
    variant1 = variant2;
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 3);
}

TEST(Variant, Destructor)
{
    Variant variant1(4);
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 4);
    
    {
        Variant variant2(variant1);
        EXPECT_TRUE(!variant1.isNull());
        EXPECT_EQ(variant1.get<int>(), 4);
    }
    
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 4);
}

TEST(Variant, IsNull)
{
    Variant variant1;
    EXPECT_TRUE(variant1.isNull());
    
    Variant variant2(variant1);
    EXPECT_TRUE(variant2.isNull());
    
    Variant variant3((const char*) "foo");
    EXPECT_TRUE(!variant3.isNull());
    
    variant3.reset();
    EXPECT_TRUE(variant3.isNull());
    
    variant3.set(0.5);
    EXPECT_TRUE(!variant3.isNull());
}

TEST(Variant, Is)
{
    Variant variant1;
    EXPECT_TRUE(variant1.is<void>());
    EXPECT_FALSE(variant1.is<int>());
    EXPECT_FALSE(variant1.is<std::string>());
    EXPECT_FALSE(variant1.is<double*>());
    EXPECT_FALSE(variant1.is<Variant>());
    
    Variant variant2(10);
    EXPECT_FALSE(variant2.is<void>());
    EXPECT_TRUE(variant2.is<int>());
    EXPECT_FALSE(variant2.is<std::string>());
    EXPECT_FALSE(variant2.is<double*>());
    EXPECT_FALSE(variant2.is<Variant>());
    
    Variant variant3(std::string("foo"));
    EXPECT_FALSE(variant3.is<void>());
    EXPECT_FALSE(variant3.is<int>());
    EXPECT_TRUE(variant3.is<std::string>());
    EXPECT_FALSE(variant3.is<double*>());
    EXPECT_FALSE(variant3.is<Variant>());
    
    double tab[] = { 0.5, 1.0, 1.5, 2.0 };
    
    variant1.set((double*) tab);
    EXPECT_FALSE(variant1.is<void>());
    EXPECT_FALSE(variant1.is<int>());
    EXPECT_FALSE(variant1.is<std::string>());
    EXPECT_TRUE(variant1.is<double*>());
    EXPECT_FALSE(variant1.is<Variant>());
    
    Variant variant4(variant3);
    EXPECT_FALSE(variant4.is<void>());
    EXPECT_FALSE(variant4.is<int>());
    EXPECT_TRUE(variant4.is<std::string>());
    EXPECT_FALSE(variant4.is<double*>());
    EXPECT_FALSE(variant4.is<Variant>());
    
    variant2.set(variant4);
    EXPECT_FALSE(variant2.is<void>());
    EXPECT_FALSE(variant2.is<int>());
    EXPECT_FALSE(variant2.is<std::string>());
    EXPECT_FALSE(variant2.is<double*>());
    EXPECT_TRUE(variant2.is<Variant>());
}

std::ostream& operator<<(std::ostream& stream, const std::type_info& info)
{
    stream << info.name();
    return stream;
}

TEST(Variant, Type)
{
    Variant variant1;
    EXPECT_EQ(variant1.type(), typeid(void));
    EXPECT_NE(variant1.type(), typeid(int));
    EXPECT_NE(variant1.type(), typeid(std::string));
    EXPECT_NE(variant1.type(), typeid(double*));
    EXPECT_NE(variant1.type(), typeid(Variant));
    
    Variant variant2(10);
    EXPECT_NE(variant2.type(), typeid(void));
    EXPECT_EQ(variant2.type(), typeid(int));
    EXPECT_NE(variant2.type(), typeid(std::string));
    EXPECT_NE(variant2.type(), typeid(double*));
    EXPECT_NE(variant2.type(), typeid(Variant));
    
    Variant variant3(std::string("foo"));
    EXPECT_NE(variant3.type(), typeid(void));
    EXPECT_NE(variant3.type(), typeid(int));
    EXPECT_EQ(variant3.type(), typeid(std::string));
    EXPECT_NE(variant3.type(), typeid(double*));
    EXPECT_NE(variant3.type(), typeid(Variant));
    
    double tab[] = { 0.5, 1.0, 1.5, 2.0 };
    
    variant1.set((double*) tab);
    EXPECT_NE(variant1.type(), typeid(void));
    EXPECT_NE(variant1.type(), typeid(int));
    EXPECT_NE(variant1.type(), typeid(std::string));
    EXPECT_EQ(variant1.type(), typeid(double*));
    EXPECT_NE(variant1.type(), typeid(Variant));
    
    Variant variant4(variant3);
    EXPECT_NE(variant4.type(), typeid(void));
    EXPECT_NE(variant4.type(), typeid(int));
    EXPECT_EQ(variant4.type(), typeid(std::string));
    EXPECT_NE(variant4.type(), typeid(double*));
    EXPECT_NE(variant4.type(), typeid(Variant));
    
    variant2.set(variant4);
    EXPECT_NE(variant2.type(), typeid(void));
    EXPECT_NE(variant2.type(), typeid(int));
    EXPECT_NE(variant2.type(), typeid(std::string));
    EXPECT_NE(variant2.type(), typeid(double*));
    EXPECT_EQ(variant2.type(), typeid(Variant));
}

TEST(Variant, Reset)
{
    Variant variant1;
    EXPECT_TRUE(variant1.isNull());
    
    variant1.set(5);
    EXPECT_EQ(variant1.get<int>(), 5);
    EXPECT_TRUE(!variant1.isNull());
    
    variant1.reset();
    EXPECT_TRUE(variant1.isNull());
    
    Variant variant2((char*) "foobarbaz");
    EXPECT_TRUE(!variant2.isNull());
    EXPECT_EQ(variant2.get<char*>(), "foobarbaz");
    
    Variant variant3(variant2);
    EXPECT_TRUE(!variant3.isNull());
    EXPECT_EQ(variant3.get<char*>(), "foobarbaz");
    
    variant2.reset();
    EXPECT_TRUE(variant2.isNull());
    EXPECT_TRUE(!variant3.isNull());
}

static const int DEFAULT = 42;

struct foo {
    foo(int value = DEFAULT)
        : value(value)
    {
    }
    
    bool operator==(const foo& f) const
    {
        return value == f.value;
    }

    int value;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector)
{
    typename std::vector<T>::const_iterator it = vector.begin();
    typename std::vector<T>::const_iterator end = vector.end();

    while (it != end) {
        stream << *it;
        if (++it != end)
            stream << ", ";
    }
    
    return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::list<T>& list)
{
    typename std::list<T>::const_iterator it = list.begin();
    typename std::list<T>::const_iterator end = list.end();

    while (it != end) {
        stream << *it;
        if (++it != end)
            stream << ", ";
    }
    
    return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::set<T>& set)
{
    typename std::set<T>::const_iterator it = set.begin();
    typename std::set<T>::const_iterator end = set.end();

    while (it != end) {
        stream << *it;
        if (++it != end)
            stream << ", ";
    }
    
    return stream;
}

TEST(Variant, Get)
{
    Variant variant1(100);
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 100);
    
    variant1.reset();
    EXPECT_TRUE(variant1.isNull());
    EXPECT_EQ(variant1.get<foo>().value, DEFAULT);
    
    variant1.set(foo(50));
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.type(), typeid(foo));
    EXPECT_EQ(variant1.get<foo>().value, 50);
    
    int b = 100;
    Variant variant2(&b);
    EXPECT_EQ(*variant2.get<int*>(), 100);
    
    long numbers[] = { 4, 8, 15, 16, 23, 42 };
    std::vector<long> vector(numbers, numbers + 4);
    
    Variant variant3(vector);
    EXPECT_TRUE(!variant3.isNull());
    EXPECT_EQ(variant3.type(), typeid(std::vector<long>));
    EXPECT_EQ(variant3.get<std::vector<long> >(), vector);
    EXPECT_EQ(variant3.get<std::list<long> >(), std::list<long>());
    
    {
        Variant variant4(variant3);
        EXPECT_TRUE(!variant4.isNull());
        EXPECT_EQ(variant4.type(), typeid(std::vector<long>));
        EXPECT_EQ(variant4.get<std::vector<long> >(), vector);
    }
    
    EXPECT_TRUE(!variant3.isNull());
    EXPECT_EQ(variant3.type(), typeid(std::vector<long>));
    EXPECT_EQ(variant3.get<std::vector<long> >(), vector);
    
    std::vector<Variant> variants;
    Variant variant5(0);
    variants.push_back(variant5);
    
    for (int i = 1; i < 10; ++i) {
        Variant variant6(variant5);
        variants.push_back(variant6);
    }
    
    for (int i = variants.size() - 1; i >= 0; --i) {
        Variant variant7 = variants[i];
        EXPECT_TRUE(!variant7.isNull());
        EXPECT_EQ(variant7.type(), typeid(int));
        EXPECT_EQ(variant7.get<int>(), 0);
        if (i % 2 == 0)
            variants.pop_back();
    }
}

TEST(Variant, Set)
{
    Variant variant1;
    EXPECT_TRUE(variant1.isNull());
    
    variant1.set(100);
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 100);
    
    Variant variant2(variant1);
    EXPECT_TRUE(!variant2.isNull());
    EXPECT_EQ(variant2.get<int>(), 100);
    
    variant1.set(200);
    EXPECT_TRUE(!variant1.isNull());
    EXPECT_EQ(variant1.get<int>(), 200);
    EXPECT_TRUE(!variant2.isNull());
    EXPECT_EQ(variant2.get<int>(), 100);
    EXPECT_EQ(variant2.type(), typeid(int));
    
    variant2.set(100.5);
    EXPECT_EQ(variant2.type(), typeid(double));
    
    variant2.set(foo(50));
    EXPECT_EQ(variant2.type(), typeid(foo));
    EXPECT_EQ(variant2.get<foo>().value, 50);
    
    variant2.set(foo());
    EXPECT_EQ(variant2.get<foo>().value, DEFAULT);
}

TEST(Variant, OperatorAssign)
{
    Variant variant1;
    
    Variant variant2 = variant1;
    EXPECT_TRUE(variant2.isNull());
    
    Variant variant3;
    variant3.set<int>(1);
    
    Variant variant4 = variant3;
    EXPECT_TRUE(!variant4.isNull());
    EXPECT_EQ(variant4.get<int>(), 1);
    
    variant3.reset();
    EXPECT_TRUE(!variant4.isNull());
    EXPECT_EQ(variant4.get<int>(), 1);
    EXPECT_EQ(variant4.type(), typeid(int));
    
    Variant variant5(variant4 = Variant(std::string("foo")));
    EXPECT_EQ(variant4.get<std::string>(), std::string("foo"));
    EXPECT_EQ(variant4.type(), typeid(std::string));
    EXPECT_EQ(variant4.get<foo>().value, DEFAULT);
    EXPECT_EQ(variant5.get<std::string>(), std::string("foo"));
    EXPECT_EQ(variant5.type(), typeid(std::string));
    
    Variant variant6;
    variant6.set(std::set<float>());
    EXPECT_TRUE(!Variant(variant6 = variant6).isNull());
    EXPECT_TRUE(!variant6.isNull());
    EXPECT_EQ(variant6.type(), typeid(std::set<float>));
    EXPECT_EQ(variant6.get<std::set<float> >(), std::set<float>());
}

TEST(Variant, OperatorEquals)
{
    EXPECT_TRUE(Variant() == Variant());
    
    Variant variant1;
    Variant variant2(variant1);
    EXPECT_TRUE(variant1 == variant2);
    
    variant1.set<char>('a');
    variant2.set<char>('a');
    EXPECT_TRUE(variant1 == variant2);
    
    variant2.reset();
    EXPECT_FALSE(variant1 == variant2);
    
    variant1.set<char>('b');
    EXPECT_FALSE(variant1 == variant2);
    
    variant2.set<int>('b');
    EXPECT_FALSE(variant1 == variant2);
}

TEST(Variant, OperatorNotEquals)
{
    EXPECT_FALSE(Variant() != Variant());
    
    Variant variant1;
    Variant variant2(variant1);
    EXPECT_FALSE(variant1 != variant2);
    
    variant1.set<char>('a');
    variant2.set<char>('a');
    EXPECT_FALSE(variant1 != variant2);
    
    variant2.reset();
    EXPECT_TRUE(variant1 != variant2);
    
    variant1.set<char>('b');
    EXPECT_TRUE(variant1 != variant2);
    
    variant2.set<int>('b');
    EXPECT_TRUE(variant1 != variant2);
}

