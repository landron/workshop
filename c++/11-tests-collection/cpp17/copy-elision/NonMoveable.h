/*
    tag_copy_elision
    tag_nrvo
        This variant of copy elision is known as NRVO, "named return value
   optimization".

        "Unfortunately, in C++17 we'll get copy elision only for temporary
   objects, not for Named RVO (so it covers only the first point, not for Named
   Return Value Optimization)" (see make_2)

    Reference
        https://www.bfilipek.com/2017/06/cpp17-details-clarifications.html#guaranteed-copy-elision
        https://en.cppreference.com/w/cpp/language/copy_elision
*/

#pragma once

#include <array>

struct NonMoveable {
    NonMoveable(int);
    // no copy or move constructor:
    NonMoveable(const NonMoveable&) = delete;
    NonMoveable(NonMoveable&&) = delete;

    std::array<int, 1024> arr;
};

NonMoveable::NonMoveable(int init) {
    arr.fill(init);
}

/*
    C++ 14:
        error C2280: 'NonMoveable::NonMoveable(NonMoveable &&)': attempting to
   reference a deleted function

   C++ 17: No move or copy occurs by definition. The deleted move constructor is
   completely ignored.
   prvalue: pure rvalue (no memory address vs Rvalue: Any expression that can be
   moved from.)
*/
NonMoveable make() {
    return NonMoveable(42);
}
