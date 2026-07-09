/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_destructor() {
    Derived2 d;
    Derived2::sliceExample(d); // it works
    Derived2::sliceExample(static_cast<Base>(d));
}
