#pragma once

#include <utility>
#include <vector>

namespace math_lib
{

using Primes = std::vector<unsigned>;
using Divisors = std::vector<std::pair<unsigned, unsigned>>;

Primes get_primes(unsigned);
Divisors get_prime_divisors(unsigned, const Primes& primes);
}
