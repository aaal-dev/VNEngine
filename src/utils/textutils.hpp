#pragma once

#include <string>
#include <algorithm>


namespace TextUtils {

/**
 * @brief Create a new string with lowercase letters from passed in string 
 * @param str Reference string
 * @return New string with lowercase letters
 */
template <typename T>
static std::basic_string<T> toLowerCase(std::basic_string<T> const &str)
{
    std::basic_string<T> s2 = str;
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return std::move(s2);
};

/**
 * @brief Convert a string to lowercase 
 * @param str String that needs to be convert
 * @return Converted string
 */
template <typename T>
inline std::basic_string<T>& toLowerCase(std::basic_string<T> &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
};

/**
 * @brief Uppercases string
 * @param str 
 * @return New string with lowercase letters
 */
template <typename T>
static std::basic_string<T> toUpperCase(std::basic_string<T> const &s)
{
    std::basic_string<T> s2 = s;
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    return std::move(s2);
};

/**
 * @brief
 * @param str 
 * @return
 */
template <typename T>
static std::basic_string<T> toCapitalFirst(std::basic_string<T> const &str)
{
    std::basic_string<T> s2 = str;
	std::transform(s2.begin(), s2.begin()+1, s2.begin(),  ::toupper);
	std::transform(s2.begin()+1, s2.end(),   s2.begin()+1,::tolower);
    return std::move(s2);
};

}
