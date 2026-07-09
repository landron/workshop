/*
ninja
./cpp_tests
*/
#include <iostream>

#ifndef TEST_CPP_14
// vcpkg providing gtest => #include <gtest/gtest.h> is the right choice.
#include <gtest/gtest.h>
#else
#include <cassert>
#define ASSERT_TRUE(expr) assert(expr)
#endif
//  copy elision
#include "NonMoveable.h"

#ifndef TEST_CPP_14
TEST(test_copy_elision, test1)
#else
int main()
#endif
{
    const auto largeNonMovableObj = make();
    ASSERT_TRUE(largeNonMovableObj.arr.size() > 30);
    constexpr auto index = 42;
    std::cout << "Value " << index << ": " << largeNonMovableObj.arr.at(index)
              << '.' << std::endl;
    ASSERT_TRUE(29 == largeNonMovableObj.arr.at(29));
    ASSERT_TRUE(29 == largeNonMovableObj.arr.at(61));
}
