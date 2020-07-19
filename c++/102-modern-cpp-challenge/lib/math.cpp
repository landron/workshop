#include "math.h"

#include <gtest/gtest.h>
#include <cassert>
#include <cmath>

#include "utils.h"

using Primes = std::vector<unsigned>;

/*
    Reference
        proj_euler.py/get_primes_2

    Return value
        no cost: the vector will be just moved
*/
Primes get_primes(unsigned limit)
{
    if (limit < 3)
        return {};

    Primes primes;

    std::vector<unsigned> sieve_of_Eratosthenes;
    sieve_of_Eratosthenes.resize(limit/2);
    for (auto i = 0; i < sieve_of_Eratosthenes.size() - 1; ++i)
        sieve_of_Eratosthenes[i] = i*2 + 3;
    auto& sieve = sieve_of_Eratosthenes;

    const auto limit_of_sieve = 1 + std::floor(std::sqrt(limit));
    for (auto i = 3; i < limit_of_sieve; i += 2)
        if (sieve[i/2-1])
            for (size_t j = i*i; j < limit; j += 2*i)
                sieve[j/2-1] = 0;

    primes.push_back(2);
    for (auto i = 0; i < sieve.size(); ++i)
        if (sieve[i])
            primes.push_back(sieve[i]);

    return primes;
}

std::vector<std::pair<unsigned, unsigned>> get_prime_divisors(unsigned, const Primes&)
{
    using Divisors = std::vector<std::pair<unsigned, unsigned>>;
    return Divisors();
}

TEST(math, get_primes)
{
    ASSERT_EQ(Primes({}), get_primes(2));
    ASSERT_EQ(Primes({2, 3}), get_primes(5));
    ASSERT_EQ(Primes({2, 3, 5, 7}), get_primes(10));
    ASSERT_EQ(25, get_primes(100).size());

    if (0)
    std::cout << "get_primes(5) " << get_primes(100).size() << "." << std::endl;
}
