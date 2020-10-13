#pragma once

#include <utility>
#include <vector>

namespace math_lib
{

using Primes = std::vector<unsigned>;
using Divisors = std::vector<std::pair<unsigned, unsigned>>;
using ProperDivisors = Primes;

Primes get_primes(unsigned);
Divisors get_prime_divisors(unsigned, const Primes& primes);

// This is still slow
ProperDivisors get_proper_divisors(const Divisors& prime_divisors);
}
