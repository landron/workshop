#pragma once

#include <print>

class Base {
  protected:
    ~Base() =
        default; // Forces compilation error on by-value destruction (slicing)
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

    // Fails: Per C++ standard [class.protected], Derived2 can only access protected 
    // members (like ~Base) on objects of its own type or further derived types. 
    // It is barred from destroying a raw, standalone Base object.
    static void sliceExample(Base b) {
        b.speak();
    }
};

// COMPILATION ERROR: 'Base::~Base()' is protected
//      Protection can be beaten through inheritence
void sliceExample1(Base b) {
    b.speak();
}

// The destructor of 'Derived' is public
void sliceExample2(Derived b) {
    b.speak();
}

// LEGAL: Reference preserves polymorphism
void safeExample(const Base& b) {
    b.speak();
}
