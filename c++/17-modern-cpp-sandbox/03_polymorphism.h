#pragma once

#include <vector>
#include <memory>
#include <numeric>
#include <cstdint>

// vcpkg providing gtest => #include <gtest/gtest.h> is the right choice.
#include <gtest/gtest.h>

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

    for (auto i = 0; i < count; ++i) {
        shapes.push_back(std::make_unique<Circle>(i));
        flat_circles.push_back(FlatCircle{i});
    }

    // TEST 1: Size of the container elements
#ifndef __INTELLISENSE__
    /*
        That’s a classic Empty Base Optimization (EBO) failure in the IntelliSense engine.

        Why this happened (Technical Reason)
            std::unique_ptr is defined roughly like this:

            template<typename T, typename Deleter = std::default_delete<T>>
            class unique_ptr {
                T* ptr;
                Deleter del; // This is an empty class
            };

            Real GCC: Sees Deleter is empty and uses EBO to make it occupy 0 bytes. Total = 8 bytes.

            IntelliSense: Sometimes fails the EBO check on specific Standard Library 
            implementations (like your GCC 15.2 headers), assigning 8 bytes to the pointer + 
            padding/size for the "empty" deleter. Total = 16 bytes.
    */
    if constexpr (sizeof(void*) == 8) {
        static_assert(sizeof(shapes[0]) == 8, "This only fails in VS Code's broken IntelliSense");
    }
#endif
    // std::println("Actual size of shapes[0] (unique_ptr<Shape>): {}", sizeof(shapes[0]));

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
