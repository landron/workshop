/*
    Solution 1: protected destructor in the base class
    "You may inherit from me, but you may not own/delete me through a Base
   interface."
*/
#pragma once

#include <print>

class Base {
  protected:
    // Forces compilation error on by-value destruction (slicing)
    ~Base() = default;

  public:
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

    static void sliceExample(Derived b) {
        b.speak();
    }

    // OK: Unlike a free function, a member of a class derived from Base has
    // access to Base's protected destructor, so this by-value parameter is
    // legal.
    static void sliceExample(Base b) {
        b.speak();
    }
};

// COMPILATION ERROR: 'Base::~Base()' is protected
//      Protection can be beaten through inheritence
void sliceExample1(Base b) {
    b.speak();
}

// OK: Derived has a public destructor. Destroying the parameter calls
// Derived::~Derived(), which is allowed to invoke Base::~Base().
void sliceExample2(Derived b) {
    b.speak();
}

// LEGAL: Reference preserves polymorphism
void safeExample(const Base& b) {
    b.speak();
}
