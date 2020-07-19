#pragma once

#include "lib/math.h"

namespace modern_cpp_challenge
{
    using BigInteger = unsigned long long;

    BigInteger sum_of_divisible_3_5(unsigned limit);
    /*constexpr*/ unsigned get_greatest_common_divisor(unsigned, unsigned);
    unsigned get_least_common_multiple(const std::vector<unsigned>&);

    unsigned get_abundance(unsigned, const math_lib::Primes&);
    void print_abundant_numbers(unsigned limit);
};
