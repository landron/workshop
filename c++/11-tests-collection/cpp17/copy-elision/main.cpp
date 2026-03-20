#include <iostream>

#ifndef TEST_CPP_14
#include "gtest/gtest.h"
#else
#include <cassert>
#define ASSERT_TRUE(expr) assert(expr)
#endif
//  copy elision
#include "NonMoveable.h"

#ifndef TEST_CPP_14
TEST(test_sample, test1)
#else
int main()
#endif
{
    const auto largeNonMovableObj = make();
    ASSERT_TRUE(largeNonMovableObj.arr.size() > 30);
    std::cout << "Value 29: " << largeNonMovableObj.arr.at(29) << '.' << std::endl;
    ASSERT_TRUE(42 == largeNonMovableObj.arr.at(29));
    ASSERT_TRUE(42 == largeNonMovableObj.arr.at(61));
}
