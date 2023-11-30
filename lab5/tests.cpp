#include <gtest/gtest.h>
#include "list.h"
#include "allocator.h"

//Allocator

TEST(alloc, test1)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v[0], 12);
}

TEST(alloc, test2)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v[0], 12);
    EXPECT_EQ(v[1], 34);
    EXPECT_EQ(v[2], 56);
}

TEST(alloc, test3)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v.size(), 1);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v.size(), 3);
}

TEST(alloc, test4)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v.size(), 1);
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

TEST(alloc, test5)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v.size(), 3);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

//List

TEST(List, test1)
{
    List<int> l;
    EXPECT_EQ(l.getsize(), 0); 
}

TEST(List, test2)
{
    List<int> l;
    l.push(12);
    EXPECT_EQ(l.getsize(), 1); 
}

TEST(List, test3)
{
    List<int> l;
    l.push(12);
    EXPECT_EQ(l.getsize(), 1); 
    l.pop();
    EXPECT_EQ(l.getsize(), 0);
}


TEST(List, test4)
{
    List<int> l;
    l.push(66);
    
    EXPECT_EQ(l.end(), nullptr);
}


TEST(List, test5)
{
    List<int> l;
    l.push(66);
    l.push(78);
    l.push(90);
    
    EXPECT_EQ(l.getsize(), 3);
}