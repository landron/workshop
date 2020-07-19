/*
    The direct solution (find the divisors by trying all the smaller numbers) is much simpler, but less
        C++ enriching.
*/
#include <gtest/gtest.h>
#include "problems.h"

#include <iostream>
#include <numeric>

unsigned modern_cpp_challenge::get_abundance(unsigned number, const math_lib::Primes& primes)
{
    const auto prime_divs = math_lib::get_prime_divisors(number, primes);
    if (prime_divs.empty())
        std::cout << "prime_divs.empty(): " << number << std::endl;

    const auto divs =
        math_lib::get_proper_divisors(
            math_lib::get_prime_divisors(number, primes));
    const auto sum = std::accumulate(divs.begin(), divs.end(), 0u);
    return sum > number ? (sum - number) : 0;
}

void modern_cpp_challenge::print_abundant_numbers(unsigned limit)
{
    const auto primes = math_lib::get_primes(limit);
    for (decltype(limit) i = 2; i < limit; ++i)
    {
        const auto abundance = get_abundance(i, primes);
        if (abundance)
            std::cout << "(" << i << ":" << abundance << ")" << std::endl;
    }
}

TEST(test_p06, main)
{
    using namespace modern_cpp_challenge;

    const auto primes_1000 = math_lib::get_primes(1000);
    ASSERT_EQ(4, get_abundance(12, primes_1000));
    ASSERT_EQ(0, get_abundance(16, primes_1000));
    ASSERT_EQ(3, get_abundance(18, primes_1000));
    ASSERT_EQ(2, get_abundance(20, primes_1000));
    ASSERT_EQ(12, get_abundance(24, primes_1000));
    //std::cout << get_abundance(18, primes_1000) << std::endl;
}
