#pragma once

#include <string>
#include <algorithm>


class textutils {
public:
//
//  Lowercases string
//
template <typename T>
static std::basic_string<T> lowercase(std::basic_string<T> const &s)
{
    std::basic_string<T> s2 = s;
    std::transform(s2.begin(), s2.end(), s2.begin(), tolower);
    return s2;
};

//
// Uppercases string
//
template <typename T>
static std::basic_string<T> uppercase(std::basic_string<T> const &s)
{
    std::basic_string<T> s2 = s;
    std::transform(s2.begin(), s2.end(), s2.begin(), toupper);
    return std::move(s2);
};

};

#define STRTOUCFIRST(x) std::transform (x.begin(), x.begin()+1, x.begin(),  ::toupper); std::transform (x.begin()+1, x.end(),   x.begin()+1,::tolower)
