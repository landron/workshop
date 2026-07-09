/*
ctest -V
*/
#include "NonMoveable.h"

/*
    Environment: VS 2017 / C++20
    Error: C2280 'NonMoveable::NonMoveable(NonMoveable &&)': attempting to
        reference a deleted function

    Reason:
    - 'obj' is a named local variable. Returning it implicitly treats it as an rvalue, 
    preferring a move over a copy.
    - NRVO (Named Return Value Optimization) is *optional*, not guaranteed.
    - Because the compiler might not elide the copy/move, it must verify a 
      valid fallback (the Move Constructor) exists. Since it is deleted, compilation fails.
*/
NonMoveable make_2() {
    auto obj = NonMoveable(42);
    return obj;
}
