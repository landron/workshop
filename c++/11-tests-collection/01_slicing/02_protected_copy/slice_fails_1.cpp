/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_copy() {
    protected_copy::Derived d;
    sliceExample1(d);
}
