/*
    Solution 2: protected copy in the base class

    The base class copy constructor and copy assignment operator are protected,
    preventing code outside the inheritance hierarchy from copying a Base
    object. This blocks accidental slicing through Base-by-value APIs.

    Derived classes can still choose to expose copying by defining their own
    public copy constructor and assignment operator.
*/
#pragma once

#include <print>

namespace protected_copy {

class Base {
  protected:
    // Prevents copying a/assignment Base object from outside derived classes.
    // This makes accidental slicing into a standalone Base object impossible.
    Base(const Base&) = default;
    Base& operator=(const Base&) = default;

  public:
    Base() = default;
    virtual ~Base() = default;

    virtual void speak() const {
        std::println("Base");
    }
};

class Derived : public Base {
  public:
    void speak() const override {
        std::println("Derived");
    }
};

class Derived2 : public Derived {
  public:
    void speak() const override {
        std::println("Derived 2");
    }

    // Allowed: Derived has its own public copy operations (implicit).
    // The object is sliced from Derived2 to Derived, not to Base.
    static void sliceExample(Derived b) {
        b.speak();
    }

    // Error: Base copy constructor is protected, so a Base value cannot be
    // created from outside the hierarchy.
    static void sliceExample(Base b) {
        b.speak();
    }
};

// Error: Base copy constructor is protected, preventing Base slicing.
void sliceExample1(Base b) {
    b.speak();
}

// Allowed: Derived is copyable, so slicing to Derived is still possible.
void sliceExample2(Derived b) {
    b.speak();
}

// Legal: Passing by reference avoids copying and preserves polymorphism.
void safeExample(const Base& b) {
    b.speak();
}

} // namespace protected_copy
