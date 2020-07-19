#include "math.h"

#include <gtest/gtest.h>
#include <cassert>
#include <cmath>

#include "utils.h"

#include <set>

using namespace math_lib;

/*
    Reference
        proj_euler.py/get_primes_2

    Return value
        no cost: the vector will be just moved
*/
Primes math_lib::get_primes(unsigned limit)
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
    for (size_t i = 3; i < limit_of_sieve; i += 2)
        if (sieve[i/2-1])
            for (size_t j = i*i; j < limit; j += 2*i)
                sieve[j/2-1] = 0;

    primes.push_back(2);
    for (auto i = 0; i < sieve.size(); ++i)
        if (sieve[i])
            primes.push_back(sieve[i]);

    return primes;
}

/*
    Reference
        proj_euler.py/get_prime_divisors
*/
Divisors math_lib::get_prime_divisors(unsigned number, const Primes& primes)
{
    const auto get_power = [](auto& number, auto divisor)
    {
        using NumberType = std::remove_reference<decltype(number)>::type;

        assert(number % divisor == 0);
        NumberType power{};
        while (number % divisor == 0)
        {
            power += 1;
            number /= divisor;
        }
        return power;
    };

    Divisors divisors;
    const auto limit = 1 + std::floor(std::sqrt(number));
    for (auto i : primes)
    {
        if (limit < i)
            break;
        if (number % i)
            continue;
        divisors.push_back(std::make_pair(i, get_power(number, i)));
        if (number == 1)
            break;
    }

    return divisors;
}

/*
    tag_recursive_lambda
    #recursive_lambda
*/
ProperDivisors math_lib::get_proper_divisors(const Divisors& prime_divisors)
{
    assert(!prime_divisors.empty());
    //std::cout << "get_proper_divisors: " << to_string(prime_divisors) << std::endl;

    using AllDivisors = std::set<Primes::value_type>;

    //std::function<auto(auto,const Divisors&, size_t, auto, AllDivisors&) get_all_combinations;
    const auto get_all_combinations =
        [](const Divisors& prime_divisors, size_t where, auto current,
           AllDivisors& result
           )
    {
        const auto get_all_combinations_impl =
        [](const Divisors& prime_divisors, size_t where, auto current,
           AllDivisors& result, auto& get_all_combinations_func
           ) -> void
        {
            using NumberType = std::remove_reference<decltype(current)>::type;

            // 0 = without
            for (NumberType i = 0, factor = 1; i <= prime_divisors[where].second;
                 ++i, factor *= prime_divisors[where].first)
            {
                const auto next = current * factor;
                //std::cout << "get_all_combinations: " << current << "," << factor << std::endl;
                result.insert(next);
                if (where + 1 < prime_divisors.size())
                    get_all_combinations_func(prime_divisors, where+1, next,
                        result, get_all_combinations_func);
            }
        };

        return get_all_combinations_impl(prime_divisors, where, current,
                    result, get_all_combinations_impl);
    };

    AllDivisors result{1};
    get_all_combinations(prime_divisors, 0u, 1u, result);
    ProperDivisors divisors;
    for (auto i : result)
    {
        //std::cout << i << " ";
        divisors.push_back(i);
    }
    // not the number itself
    divisors.pop_back();
    //std::cout << std::endl;
    return divisors;
}

TEST(math, get_primes)
{
    using namespace math_lib;

    ASSERT_EQ(Primes({}), get_primes(2));
    ASSERT_EQ(Primes({2, 3}), get_primes(5));
    ASSERT_EQ(Primes({2, 3, 5, 7}), get_primes(10));
    ASSERT_EQ(25, get_primes(100).size());

    if (0)
    std::cout << "get_primes(5) " << get_primes(100).size() << "." << std::endl;
}

TEST(math, get_prime_divisors)
{
    using namespace math_lib;

    const auto primes_1000 = get_primes(1000);
    ASSERT_EQ((Divisors{{2u,2u}}), get_prime_divisors(4, primes_1000));
    ASSERT_EQ((Divisors()), get_prime_divisors(5, primes_1000));
    ASSERT_EQ((Divisors{{2u,1u}, {3u,1u}}), get_prime_divisors(6, primes_1000));
    ASSERT_EQ((Divisors{{2u,3u}}), get_prime_divisors(8, primes_1000));
    ASSERT_EQ((Divisors{{2u,3u}, {7u,1u}}), get_prime_divisors(56, primes_1000));
    ASSERT_EQ((Divisors{{2u,3u}, {3u,2u}}), get_prime_divisors(72, primes_1000));

/*    std::cout << "get_prime_divisors(100) "
              << to_string(get_prime_divisors(100, primes_1000)) << "." << std::endl;*/
}

TEST(math, get_proper_divisors)
{
    using namespace math_lib;
    using Divs = Primes;

    const auto primes_1000 = get_primes(1000);
    ASSERT_EQ(Divs({1, 2, 3}), get_proper_divisors(get_prime_divisors(6, primes_1000)));
    ASSERT_EQ(Divs({1, 2, 4}), get_proper_divisors(get_prime_divisors(8, primes_1000)));
    ASSERT_EQ(Divs({1, 2, 3, 4, 6}), get_proper_divisors(get_prime_divisors(12, primes_1000)));
    ASSERT_EQ(Divs({1, 2, 3, 4, 6, 8, 12}), get_proper_divisors(get_prime_divisors(24, primes_1000)));
}