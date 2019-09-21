/*
    BigInteger vs int
*/
#include "gtest/gtest.h"
#include "problems.h"

#include <iostream>

namespace {

    using BigInteger = modern_cpp_challenge::BigInteger;
    //using BigInteger = unsigned;

/*
    O(N)
*/
auto sum_of_divisible_3_5_direct(unsigned limit)
{
    BigInteger sum_of = 0;
    for (size_t i = 1; i < limit; ++i)
        if (i%3 == 0)
            sum_of += i;
        else if (i%5 == 0)
            sum_of += i;
    return sum_of;
}

/*
    O(1)
*/
auto sum_of_divisible_3_5_smart(unsigned limit) -> BigInteger
{
    if (limit == 0)
        return 0;
    --limit;

    const auto n3 = static_cast<unsigned>(limit/3);
    const auto n5 = static_cast<unsigned>(limit/5);
    const auto n15 = static_cast<unsigned>(limit/15);

    const auto sum_to_n = [](unsigned limit)
    {
        const auto sum_of = static_cast<BigInteger>(limit)*(limit+1)/2;
        //sum_of *= static_cast<BigInteger>(factor);
        return sum_of;
    };
    return 3*sum_to_n(n3) + 5*sum_to_n(n5) - 15*sum_to_n(n15);
}

};

modern_cpp_challenge::BigInteger modern_cpp_challenge::sum_of_divisible_3_5(unsigned limit)
{
    return sum_of_divisible_3_5_smart(limit);
}

TEST(test_p01, main)
{
    ASSERT_TRUE(0 == sum_of_divisible_3_5_direct(2));
    ASSERT_TRUE(0 == sum_of_divisible_3_5_smart(2));
    ASSERT_TRUE(3 == sum_of_divisible_3_5_direct(5));
    ASSERT_TRUE(3 == sum_of_divisible_3_5_smart(5));

    for (unsigned i = 0; i < 150; ++i) {
        //std::cout << i << ": " << sum_of_divisible_3_5_direct(i) << ", " << sum_of_divisible_3_5_smart(i) << "\n";
        ASSERT_TRUE(sum_of_divisible_3_5_direct(i) == sum_of_divisible_3_5_smart(i));
    }

    //std::cout << "200001: " << sum_of_divisible_3_5_direct(200001) << ", " 
    //                        << sum_of_divisible_3_5_smart(200001) << "\n";
}