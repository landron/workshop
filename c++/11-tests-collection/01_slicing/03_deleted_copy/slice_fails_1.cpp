/*
ctest -V
*/
#include "Base.h"

void no_slice_protected_destructor() {
    deleted_copy::Derived d;
    deleted_copy::sliceExample1(d);
}
