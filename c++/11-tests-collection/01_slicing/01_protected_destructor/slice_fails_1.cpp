/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_destructor() {
    Derived d;
    sliceExample1(d);
}
