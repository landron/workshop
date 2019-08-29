#include <iostream>

#include "gtest/gtest.h"
#include "problems.h"

auto DO_EXECUTE = false;

using namespace modern_cpp_challenge;

TEST(test_main, all_problems)
{
	if (DO_EXECUTE)
	{
		(void)sum_of_divisible_3_5(100);
		//(void)get_greatest_common_divisor(48, 54);
	}
}