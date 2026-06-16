/*
ctest -V
*/
#include "NonMoveable.h"

/*
    Visual Studio Community 2017
    C++ 20:
        error C2280: 'NonMoveable::NonMoveable(NonMoveable &&)': attempting to
   reference a deleted function

   NRVO (Named Return Value Optimization) is optional, not mandatory.
   A move is semantically required to pass the named object out of the function
   scope. lvalue
*/
NonMoveable make_2() {
    auto obj = NonMoveable(42);
    return obj;
}
