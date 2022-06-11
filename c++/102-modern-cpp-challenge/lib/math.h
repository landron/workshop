#pragma once

#include <utility>
#include <vector>

namespace math_lib
{

using Number = unsigned;
using Primes = std::vector<Number>;
using Divisor = std::pair<Number, unsigned>;
using Divisors = std::vector<Divisor>;
using ProperDivisors = Primes;

Primes get_primes(unsigned long long);
Divisors get_prime_divisors(unsigned, const Primes& primes);

// This is still slow
ProperDivisors get_proper_divisors(const Divisors& prime_divisors);
}
