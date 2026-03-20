#pragma once

#include <vector>
#include <memory>
#include <numeric>
#include <cstdint>

#include "gtest/gtest.h"

// 1. The Polymorphic Approach (Slower)
class Shape {
public:
    virtual ~Shape() = default;
    virtual int getValue() const = 0;
};

class Circle : public Shape {
    int val;
public:
    Circle(int v) : val(v) {}
    int getValue() const override { return val; }
};

// 2. The Contiguous Approach (Faster)
struct FlatCircle {
    int val;
    int getValue() const { return val; }
};

TEST(PolymorphismTest, CompareMemoryLayout) {
    constexpr auto count = 1000;

    // Vector of Pointers: Objects are scattered on the heap (Indirection)
    std::vector<std::unique_ptr<Shape>> shapes;
    // Vector of Objects: Objects are side-by-side (Contiguous)
    std::vector<FlatCircle> flat_circles;

    for (int i = 0; i < count; ++i) {
        shapes.push_back(std::make_unique<Circle>(i));
        flat_circles.push_back(FlatCircle{i});
    }

    // TEST 1: Size of the container elements
    if constexpr (sizeof(void*) == 8) {
        static_assert(sizeof(shapes[0]) == 8, "TODO: it fails in VSCode’s IntelliSense");
    }
    static_assert(sizeof(int) == 4, "Expected int size to be 4 bytes");
    // The pointer vector stores 8-byte addresses. The flat vector stores 4-byte ints.
    EXPECT_EQ(sizeof(shapes[0]), sizeof(void*)); // Size of unique_ptr<Shape> 
    EXPECT_EQ(sizeof(flat_circles[0]), sizeof(int)); // Size of FlatCircle (4-byte int)

    // TEST 2: Logic Check
    int sum_poly = 0;
    for (const auto& s : shapes) sum_poly += s->getValue(); // VTable lookup + Pointer hop

    int sum_flat = 0;
    for (const auto& c : flat_circles) sum_flat += c.getValue(); // Direct call + Cache friendly

    EXPECT_EQ(sum_poly, sum_flat);
}
