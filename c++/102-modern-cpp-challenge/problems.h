#pragma once

namespace modern_cpp_challenge
{

    using BigInteger = unsigned long long;

    BigInteger sum_of_divisible_3_5(unsigned limit);
    /*constexpr*/ unsigned get_greatest_common_divisor(unsigned, unsigned);
    unsigned get_least_common_multiple(const std::vector<unsigned>&);
};
