/*
ctest -V
*/
#include "Base.h"

#include <gtest/gtest.h>

TEST(test_slice, derivation_allows_protection) {
    Derived2 d;
    Derived2::sliceExample(d);  // it works
    Derived2::sliceExample(static_cast<Base>(d));
}
