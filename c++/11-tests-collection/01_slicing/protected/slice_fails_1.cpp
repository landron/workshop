/*
ctest -V
*/
#include "Base.h"

#include <gtest/gtest.h>

TEST(test_slice, protected_destructor) {
    Derived d;
    sliceExample1(d);
}
