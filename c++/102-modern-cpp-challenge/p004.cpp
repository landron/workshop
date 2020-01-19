/*
    Largest prime smaller than a given number
*/
#include "gtest/gtest.h"
#include "problems.h"

#include <cassert>
#include <cmath>

namespace {

using BigInteger = modern_cpp_challenge::BigInteger;

/*
    O(n)

    Reference
        "a variant of the classic O(sqrt(N)) algorithm. It uses the fact
        that a prime (except 2 and 3) is of form 6k - 1 or 6k + 1 and
        looks only at divisors of this form"
        https://stackoverflow.com/questions/1801391/what-is-the-best-algorithm-for-checking-if-a-number-is-prime

        also in proj_euler.py
*/
bool is_prime(BigInteger number)
{
    assert(number > 0);

    if (number < 4)
        return number != 1;
    if (number%2 == 0)
        return false;
    if (number%3 == 0)
        return false;

    const auto limit = 1 + std::floor(std::sqrt(number));
    unsigned step = 2;
    for (BigInteger i = 5; i < limit; i += step, step = 6-step)
        if (number%i == 0)
            return false;

    return true;
}

/*
    O(n*n), theoretically, but prime numbers are dense enough for usual numbers
        so more like a O(n)
*/
BigInteger largest_prime_smaller_than(BigInteger number)
{
    assert(number > 2 && "condition to have a solution");
    if (number <= 2)
        throw std::exception("Number outside the range: too small!");

    while (1)
    {
        --number;
        if (is_prime(number))
            break;
    }
    return number;
}

};


TEST(test_p04, main)
{
    ASSERT_TRUE(!is_prime(1));
    ASSERT_TRUE(is_prime(2));
    ASSERT_TRUE(!is_prime(6));
    ASSERT_TRUE(is_prime(7));
    ASSERT_TRUE(is_prime(17));
    ASSERT_TRUE(!is_prime(27));
    ASSERT_TRUE(is_prime(37));
    ASSERT_TRUE(is_prime(79));
    ASSERT_TRUE(!is_prime(82));
    ASSERT_TRUE(is_prime(83));
    ASSERT_TRUE(!is_prime(111));
    ASSERT_TRUE(is_prime(113));
    ASSERT_TRUE(is_prime(127));

    // ASSERT_TRUE(0 == largest_prime_smaller_than(2)); //  C++ exception
    ASSERT_TRUE(2 == largest_prime_smaller_than(3));
    ASSERT_TRUE(73 == largest_prime_smaller_than(79));
    ASSERT_TRUE(997 == largest_prime_smaller_than(1000));
}
