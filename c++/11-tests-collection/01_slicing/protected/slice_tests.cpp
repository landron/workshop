#include "Base.h"

#include <gtest/gtest.h>

// see c++/11-tests-collection/01_slicing/protected/slice_fails_1.cpp
TEST(test_slice, derivation_allows_protection) {
    Derived2 d;
    sliceExample2(d);
}
