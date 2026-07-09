/*
    Solution 3: deleted copy in the base class

    "A polymorphic base class should not be copied by value."

    Deleting copy operations prevents accidental slicing because a Base object
    cannot be copy-constructed or assigned. Derived classes can still choose
    to support copying by explicitly defining their own copy operations.
*/
#pragma once

#include <print>

namespace deleted_copy {

class Base {
  public:
    Base() = default;
    virtual ~Base() = default;

    // Prevent copying a Base object.
    // This blocks slicing through APIs taking Base by value.
    Base(const Base&) = delete;
    Base& operator=(const Base&) = delete;

    // Explicitly disable moves as well.
    // A polymorphic object that cannot be copied should generally not be moved
    // through the Base interface either.
    Base(Base&&) = delete;
    Base& operator=(Base&&) = delete;

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

    // Error: Base copy is deleted, so slicing to Base is impossible.
    static void sliceExample(Base b) {
        b.speak();
    }

    // OK: Derived explicitly enables copying.
    // Slicing occurs from Derived2 to Derived.
    static void sliceExample(Derived b) {
        b.speak();
    }
};

// COMPILATION ERROR: Base copy constructor is deleted.
// A Base object cannot be created by slicing from Derived.
void sliceExample1(Base b) {
    b.speak();
}

// OK: Derived is explicitly copyable.
void sliceExample2(Derived b) {
    b.speak();
}

// LEGAL: Reference preserves polymorphism and does not copy.
void safeExample(const Base& b) {
    b.speak();
}

} // namespace deleted_copy
