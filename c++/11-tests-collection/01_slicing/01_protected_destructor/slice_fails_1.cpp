/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_destructor() {
    protected_destructor::Derived d;
    protected_destructor::sliceExample1(d);
}
