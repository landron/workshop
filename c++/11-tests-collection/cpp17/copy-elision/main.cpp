#include <iostream>

#include "gtest/gtest.h"
//  copy elision
#include "NonMoveable.h"

TEST(test_sample, test1)
{
    const auto largeNonMovableObj = make();
    std::cout << "Value 29: " << largeNonMovableObj.arr.at(29) << '.' << std::endl;
    ASSERT_TRUE(42 == largeNonMovableObj.arr.at(29));
    ASSERT_TRUE(42 == largeNonMovableObj.arr.at(61));
}