/*
https://leetcode.com/problems/add-binary/description

#cpp20_views_reverse
#cpp20_ranges_pipeline
#cpp23_resize_and_overwrite
#cpp23_inplace_string_write
*/
#pragma once

#include <cassert>
#include <cstring>

#include <algorithm>
#include <print>
#include <string>

namespace leetcode {

static std::string add_binary_gemini(std::string_view a, std::string_view b) {
    // 1. Optimize allocations using C++23 resize_and_overwrite
    std::string result;
    const size_t max_len = std::max(a.size(), b.size());
    result.resize_and_overwrite(
        max_len + 1, [&](char* buf, [[maybe_unused]] size_t buf_size) noexcept {
            // 2. Use C++20 views to cleanly iterate backwards without
            // complex index math
            auto r_a = a | std::views::reverse;
            auto r_b = b | std::views::reverse;

            auto it_a = r_a.begin();
            auto it_b = r_b.begin();

            int carry = 0;
            size_t out_idx = 0;

            // 3. Single unified loop processing both inputs simultaneously
            while (it_a != r_a.end() || it_b != r_b.end() || carry) {
                int sum = carry;
                if (it_a != r_a.end()) {
                    sum += (*it_a - '0');
                    ++it_a;
                }
                if (it_b != r_b.end()) {
                    sum += (*it_b - '0');
                    ++it_b;
                }

                // Bitwise operations remove conditional branching overhead
                buf[out_idx++] = (sum & 1) ? '1' : '0';
                carry = sum >> 1;
            }

            // 4. In-place reverse within the destination buffer (avoids a
            // second pass)
            std::reverse(buf, buf + out_idx);
            // Shrinks string precisely to actual generated characters
            return out_idx;
        });

    return result;
}

static std::string add_binary_chatgpt(std::string_view a, std::string_view b) {
    const auto max_len = std::max(a.size(), b.size());

    std::string result;
    result.resize_and_overwrite(max_len + 1, [&](char* out, size_t) noexcept {
        size_t ia = a.size();
        size_t ib = b.size();
        size_t pos = max_len + 1;
        int carry = 0;

        while (ia || ib || carry) {
            int sum = carry;

            if (ia) sum += a[--ia] - '0';

            if (ib) sum += b[--ib] - '0';

            out[--pos] = static_cast<char>('0' + (sum & 1));
            carry = sum >> 1;
        }

        // Move generated digits to the beginning.
        const size_t len = max_len + 1 - pos;
        std::memmove(out, out + pos, len);

        return len;
    });

    return result;
}

} // namespace leetcode

TEST(AddBinaryTest, Trivial) {
    EXPECT_EQ(leetcode::add_binary_gemini("11", "1"), "100");
    EXPECT_EQ(leetcode::add_binary_gemini("1010", "1011"), "10101");
    EXPECT_EQ(leetcode::add_binary_chatgpt("11", "1"), "100");
    EXPECT_EQ(leetcode::add_binary_chatgpt("1010", "1011"), "10101");
}

TEST(AddBinaryTest, EdgeCases) {
    EXPECT_EQ(leetcode::add_binary_gemini("", ""), "");
    EXPECT_EQ(leetcode::add_binary_gemini("0", "0"), "0");
    EXPECT_EQ(leetcode::add_binary_gemini("1", "0"), "1");
    EXPECT_EQ(leetcode::add_binary_gemini("0", "1"), "1");

    EXPECT_EQ(leetcode::add_binary_chatgpt("", ""), "");
    EXPECT_EQ(leetcode::add_binary_chatgpt("0", "0"), "0");
    EXPECT_EQ(leetcode::add_binary_chatgpt("1", "0"), "1");
    EXPECT_EQ(leetcode::add_binary_chatgpt("0", "1"), "1");
}

TEST(AddBinaryTest, CarryPropagation) {
    EXPECT_EQ(leetcode::add_binary_gemini("1", "1"), "10");
    EXPECT_EQ(leetcode::add_binary_gemini("1111", "1"), "10000");
    EXPECT_EQ(leetcode::add_binary_gemini("10111", "11001"), "110000");

    EXPECT_EQ(leetcode::add_binary_chatgpt("1", "1"), "10");
    EXPECT_EQ(leetcode::add_binary_chatgpt("1111", "1"), "10000");
    EXPECT_EQ(leetcode::add_binary_chatgpt("10111", "11001"), "110000");
}

TEST(AddBinaryTest, DifferentLengths) {
    EXPECT_EQ(leetcode::add_binary_gemini("1", "11111"), "100000");
    EXPECT_EQ(leetcode::add_binary_gemini("101", "10"), "111");

    EXPECT_EQ(leetcode::add_binary_chatgpt("1", "11111"), "100000");
    EXPECT_EQ(leetcode::add_binary_chatgpt("101", "10"), "111");
}

TEST(AddBinaryTest, LargeInput) {
    EXPECT_EQ(leetcode::add_binary_gemini("11111111111111111111", "1"),
              "100000000000000000000");

    EXPECT_EQ(leetcode::add_binary_chatgpt("11111111111111111111", "1"),
              "100000000000000000000");
}
