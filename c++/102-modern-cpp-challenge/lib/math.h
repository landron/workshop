#pragma once

#include <utility>
#include <vector>

std::vector<unsigned> get_primes(unsigned);
std::vector<std::pair<unsigned, unsigned>> get_proper_divisors(unsigned, const std::vector<unsigned>& primes);
