/*
    2. Greatest common divisor  p.46/428

    !!! constexpr
*/
#include "gtest/gtest.h"
#include "problems.h"

static
constexpr unsigned get_greatest_common_divisor(unsigned a, unsigned b)
{
    if (a < b)
        //std::swap(a, b); not constexpr
        return get_greatest_common_divisor(b, a);
    unsigned reminder = 1;
    for (reminder = a % b; reminder; a = b, b = reminder, reminder = a % b);
    return b;
}

unsigned modern_cpp_challenge::get_greatest_common_divisor(unsigned a, unsigned b)
{
    return ::get_greatest_common_divisor(a, b);
}

TEST(test_p02, main)
{
    ASSERT_TRUE(2 == get_greatest_common_divisor(4, 2));
    ASSERT_TRUE(3 == get_greatest_common_divisor(9, 12));
    ASSERT_TRUE(6 == get_greatest_common_divisor(48, 54));
    ASSERT_TRUE(8 == get_greatest_common_divisor(48, 56));
    ASSERT_TRUE(12 == get_greatest_common_divisor(48, 36));
    ASSERT_TRUE(4 == get_greatest_common_divisor(4, 4));
    ASSERT_TRUE(1 == get_greatest_common_divisor(4, 3));

    static_assert(6 == get_greatest_common_divisor(48, 54));
    static_assert(18 == get_greatest_common_divisor(108, 90));
}