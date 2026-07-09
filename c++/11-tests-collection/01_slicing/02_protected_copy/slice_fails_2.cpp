/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_copy() {
    using Base = protected_copy::Base;
    using Derived2 = protected_copy::Derived2;

    Derived2 d;
    Derived2::sliceExample(d); // it works
    Derived2::sliceExample(static_cast<Base>(d));
}
