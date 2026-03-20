/*
1. Use std::span<const T> for read-only functions. It is the modern replacement for (const T* ptr, size_t len). 
It is safer and zero-cost.
2. std::string stores its data on the heap (unless it's very short, known as Small String Optimization or SSO).
*/
#pragma once

#include <print>
#include <vector>
#include <array>
#include <span>

#include "gtest/gtest.h"

std::string to_string(std::span<const int> data) {
// std::string to_string(std::vector<int> data) {
    std::string result;
    result.reserve(data.size() * 4); // Guessing ~4 chars per int to avoid reallocations

    for (const auto& val : data) {
        // result += std::format("{}", val);
        result += std::to_string(val);
    }
    return result;
}

TEST(test_modern_cpp, test_std_span) {
    const std::vector<int> v = {1, 2, 3};
    const int a[] = {4, 5, 6};
    const std::array<int, 3> sa = {7, 8, 9};

    ASSERT_TRUE("123" == to_string(v));
    ASSERT_TRUE("456" == to_string(a));
    ASSERT_TRUE("789" == to_string(sa));

    if (0) {
        std::println("{}", to_string(v));  // Works
        std::println("{}", to_string(a));  // Works
        std::println("{}", to_string(sa)); // Works
    }
}
