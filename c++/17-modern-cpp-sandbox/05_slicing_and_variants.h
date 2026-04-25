#pragma once

#include <gtest/gtest.h>
#include <variant>
#include <vector>

struct Base {
    const int id;
    explicit Base(int i) : id(i) {}
    virtual ~Base() = default;

    virtual int getValue() const {
        return id;
    }
};

struct Derived : public Base {
    const int extra;
    Derived(int i, int e) : Base{i}, extra(e) {}

    int getValue() const override {
        return id + extra;
    }
};

TEST(ModernCpp, ObjectSlicing) {
    // 1. THE SLICING PROBLEM
    // A vector of Base objects (not pointers).
    std::vector<Base> sliced_vector;

    Derived d(10, 5);           // getValue() should return 15
    sliced_vector.push_back(d); // PROBLEM: Slicing happens here!

    // The 'extra' member is chopped off because the vector only allocated
    // enough space for 'Base'. The VTable is also reset to 'Base'.
    EXPECT_EQ(sliced_vector[0].getValue(), 10);
    EXPECT_NE(sliced_vector[0].getValue(), 15);
    EXPECT_EQ(sizeof(sliced_vector[0]), sizeof(Base));
}

TEST(ModernCpp, VariantSolution) {
    // 2. THE MODERN FIX: std::variant (C++17)
    // Contiguous memory, NO slicing, NO heap pointers, NO virtual table.
    using ShapeVariant = std::variant<Base, Derived>;
    std::vector<ShapeVariant> heterogeneous_contiguous_vector;

    heterogeneous_contiguous_vector.push_back(Base{10});
    heterogeneous_contiguous_vector.push_back(Derived{10, 5});

    // We use std::visit to handle the different types
    int total = 0;
    for (const auto& v : heterogeneous_contiguous_vector) {
        total += std::visit([](auto&& arg) { return arg.getValue(); }, v);
    }

    EXPECT_EQ(total, 25); // 10 from Base + 15 from Derived. NO SLICING!
}
