/*
    8. Armstrong numbers
    Write a program that prints all Armstrong numbers with three digits

        List of narcissistic numbers: https://oeis.org/A005188
*/
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "problems.h"

#include <cmath>
#include <vector>

namespace 
{

auto get_number_of_digits(unsigned number)
{
    assert(number);

    unsigned digits = 0; 
    for (;number; ++digits, number /= 10);
    return digits;
}

/*
    In number theory, a narcissistic number, in a given number base b is a number that is the sum of its own digits each raised to the power of the number of digits.
*/
bool is_narcissistic(unsigned number, unsigned digits = 0)
{
    if (digits == 0)
        digits = get_number_of_digits(number);

    unsigned sum = 0;
    for (unsigned  i = number; i; i /= 10)
        sum += std::pow(i%10, digits);
    return sum == number;
}

//  modulo, division are more expensive than multiplication and adition
void print_narcissistic_numbers_until(unsigned limit)
{
    assert(limit > 10 && limit < 100000);

    size_t i;
    for (i = 0; i < 10; ++i)
        std::cout << i << ", ";
    auto last = 0;
    for (unsigned  digits = 1; i < limit; ++i) {
        switch (i) {
            case 10:
            case 100:
            case 1000:
            case 10000:
                ++digits;
        };
        if (is_narcissistic(i, digits)) {
            if (last)
                std::cout << last << ", ";
            last = i;
        }
    }
    if (last)
        std::cout << last << std::endl;
}

//  modulo, division are more expensive than multiplication and adition
void get_narcissistic_numbers_directly(unsigned no_of_digits, void (*callback)(unsigned, bool, void*), void* param)
{
    assert(no_of_digits);

    for (unsigned i = no_of_digits == 1 ? 0 : std::pow(10, no_of_digits-1), end = std::pow(10, no_of_digits); i < end; ++i) {
        if (is_narcissistic(i, no_of_digits)) 
            callback(i, false, param);
    }
    callback(0, true, param);
}

void get_narcissistic_numbers_generating(unsigned no_of_digits, void (*callback)(unsigned, bool, void*), void* param)
{
    assert(no_of_digits);

    std::vector<unsigned> digits;
    digits.resize(no_of_digits);

    digits[0] = 1;
    int current = no_of_digits - 1;
    while (current >= 0) {
        ++digits[current];
        if (digits[current] == 10) {
            digits[current] = 0;
            --current;
            continue;
        }
        else if (current != no_of_digits-1)
            current = no_of_digits-1;

        auto number = 0;
        auto sum = 0;
        for (auto i = 0; i < no_of_digits; ++i) {
            number = number*10 + digits[i]; 
            sum += std::pow(digits[i], no_of_digits);
        }
        if (number == sum)
            callback(number, false, param);
    }
    callback(0, true, param);
}

};

/*
    Ubuntu
            generating      directly
    6:      130 ms          134 ms
    7:      1451 ms         1536 ms
    8:      19800 ms        17475 ms        ?
            79987 ms
*/
void modern_cpp_challenge::print_narcissistic_numbers(unsigned limit, bool generate)
{
    auto print = [](unsigned number, bool is_last, void* param) {
        auto last = static_cast<unsigned*>(param);
        if (!is_last) {
            if (*last)
                std::cout << *last << ", " << std::flush;;
            *last = number;
        } 
        else if (*last)
            std::cout << *last << std::endl;
    };

    std::cout << "Printing narcisstic numbers with " << limit << " digits ...\n";
    std::cout << "\t(using " << (generate ? "generating" : "direct") << " method)" << std::endl;

    unsigned last = 0;
    if (generate)
        get_narcissistic_numbers_generating(limit, print, &last);
    else
        get_narcissistic_numbers_directly(limit, print, &last);
}

TEST(test_p8, base)
{
    ASSERT_EQ(1, get_number_of_digits(6));
    ASSERT_EQ(4, get_number_of_digits(1010));

    ASSERT_TRUE(is_narcissistic(8));
    ASSERT_FALSE(is_narcissistic(11));
    ASSERT_TRUE(is_narcissistic(153));
    ASSERT_FALSE(is_narcissistic(152));
}

TEST(test_p8, 3digits_narcissistic)
{
    const auto populate = [](unsigned number, bool is_last, void* param) {
        auto& numbers = *static_cast<std::vector<unsigned>*>(param);
        if (!is_last)
            numbers.push_back(number);
    };

    const std::vector<unsigned> expected = {153, 370, 371, 407};

    std::vector<unsigned> found;
    get_narcissistic_numbers_directly(3, populate, &found);
    ASSERT_THAT(expected, testing::ContainerEq(found));

    found.clear();
    get_narcissistic_numbers_generating(3, populate, &found);
    ASSERT_THAT(expected, testing::ContainerEq(found));
}

// 2ms
TEST(test_p8, 4digits_narcissistic)
{
    const auto populate = [](unsigned number, bool is_last, void* param) {
        auto& numbers = *static_cast<std::vector<unsigned>*>(param);
        if (!is_last)
            numbers.push_back(number);
    };

    const std::vector<unsigned> expected = {1634, 8208, 9474};

    std::vector<unsigned> found;
    get_narcissistic_numbers_directly(4, populate, &found);
    ASSERT_THAT(expected, testing::ContainerEq(found));

    found.clear();
    get_narcissistic_numbers_generating(4, populate, &found);
    ASSERT_THAT(expected, testing::ContainerEq(found));
}
