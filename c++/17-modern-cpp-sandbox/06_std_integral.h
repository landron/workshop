/*
https://leetcode.com/problems/total-waviness-of-numbers-in-range-i

./modern-cpp-sandbox --gtest_filter=TotalWavinessTest.*

16. Mathematical / Number Theory

#math_digits
#math_digit_dp_candidate
#algo_bruteforce
#algo_linear_scan
#pattern_local_extrema
#pattern_digit_triplets
#pattern_peak_valley
#perf_zero_allocation
#perf_constant_space
#impl_arithmetic_digits
*/
#pragma once

#include <ranges>

#include <gtest/gtest.h>

class Solution {
  public:
    template <std::integral T>
    [[nodiscard]] constexpr static T totalWaviness(T num1, T num2) {
        /*
        num2 == std::numeric_limits<T>::max() succeeds
        */
        T waviness = 0;
        for (auto i : std::views::iota(num1, static_cast<T>(num2)))
            waviness += wavinessFor(i);
        waviness += wavinessFor(num2);

        return waviness;
    }

  private:
    template <std::integral T>
    [[nodiscard]] constexpr static T wavinessFor(T num) noexcept {
        if (num < 100) return 0;

        auto right = num % 10;
        num /= 10;
        auto middle = num % 10;
        num /= 10;

        T waviness = 0;
        for (auto left = num % 10; num > 0;
             num /= 10, right = middle, middle = left, left = num % 10) {
            // cout << right << "," << middle << "," << left << "\n";
            if (right < middle) {
                if (middle > left) ++waviness;
            } else if (right > middle) {
                if (middle < left) ++waviness;
            }
        }

        return waviness;
    }
};

// -----------------------------------------------------------------------------
// Basic ranges
// -----------------------------------------------------------------------------

TEST(TotalWavinessTest, SingleValueLessThanThreeDigits) {
    EXPECT_EQ(Solution::totalWaviness(0, 0), 0);
    EXPECT_EQ(Solution::totalWaviness(7, 11), 0);
    EXPECT_EQ(Solution::totalWaviness(99, 100), 0);
}

TEST(TotalWavinessTest, SinglePeak) {
    EXPECT_EQ(Solution::totalWaviness(152, 152), 1);
    EXPECT_EQ(Solution::totalWaviness(394, 394), 1);
}

TEST(TotalWavinessTest, SingleValley) {
    EXPECT_EQ(Solution::totalWaviness(131, 131), 1);
    EXPECT_EQ(Solution::totalWaviness(828, 828), 1);
}

TEST(TotalWavinessTest, MonotonicDigits) {
    EXPECT_EQ(Solution::totalWaviness(12345, 12345), 0);
    EXPECT_EQ(Solution::totalWaviness(98765, 98765), 0);
}

TEST(TotalWavinessTest, RepeatedDigits) {
    EXPECT_EQ(Solution::totalWaviness(11111, 11111), 0);
    EXPECT_EQ(Solution::totalWaviness(12221, 12221), 0);
}

TEST(TotalWavinessTest, MultipleExtrema) {
    // 15151:
    // 1-5-1 peak
    // 5-1-5 valley
    // 1-5-1 peak
    EXPECT_EQ(Solution::totalWaviness(15151, 15151), 3);
}

// -----------------------------------------------------------------------------
// Small ranges
// -----------------------------------------------------------------------------

TEST(TotalWavinessTest, SmallRange) {
    EXPECT_EQ(Solution::totalWaviness(151, 152), 1 + 1);
}

TEST(TotalWavinessTest, RangeContainingMixedValues) {
    EXPECT_EQ(Solution::totalWaviness(149, 151), 0 + 1 + 1);
}

// -----------------------------------------------------------------------------
// Boundary values
// -----------------------------------------------------------------------------

TEST(TotalWavinessTest, UnsignedMaxSingleValue) {
    using T = std::uint64_t;

    constexpr auto max = std::numeric_limits<T>::max();

    EXPECT_NO_THROW({
        const auto result = Solution::totalWaviness(max, max);
        (void)result;
    });
}

TEST(TotalWavinessTest, UnsignedRangeEndingAtMax) {
    using T = std::uint32_t;

    constexpr auto max = std::numeric_limits<T>::max();

    EXPECT_NO_THROW({
        const auto result = Solution::totalWaviness(max - 1, max);
        (void)result;
    });
}

TEST(TotalWavinessTest, SignedMaxSingleValue) {
    using T = std::int64_t;

    constexpr auto max = std::numeric_limits<T>::max();

    EXPECT_NO_THROW({
        const auto result = Solution::totalWaviness(max, max);
        (void)result;
    });
}

// -----------------------------------------------------------------------------
// constexpr checks
// -----------------------------------------------------------------------------

static_assert(Solution::totalWaviness(152, 152) == 1);
static_assert(Solution::totalWaviness(131, 131) == 1);
static_assert(Solution::totalWaviness(12345, 12345) == 0);
static_assert(Solution::totalWaviness(15151, 15151) == 3);
