#include "utils.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

/*
    see https://stackoverflow.com/questions/8581832/converting-a-vectorint-to-string
*/
std::string to_string(const std::vector<unsigned>& vec)
{
    std::ostringstream oss;
    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
            std::ostream_iterator<unsigned>(oss, ","));

        // Now add the last element with no delimiter
        oss << vec.back();
    }
    return oss.str();
}

std::string to_string(const std::vector<std::pair<unsigned,unsigned>>& vec)
{
    const auto toString = [](const std::pair<size_t, size_t>& data)
    {
        std::ostringstream str;
        str << "(" << data.first << "," << data.second << ")";
        return str.str();
    };

    std::ostringstream oss;
    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::transform(vec.begin(), vec.end()-1,
            std::ostream_iterator<std::string>(oss, ", "), toString);

        // Now add the last element with no delimiter
        oss << toString(vec.back());
    }
    return oss.str();
}