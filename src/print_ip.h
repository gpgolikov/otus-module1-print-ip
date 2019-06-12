/// @file print_ip.h
/// @brief File contains print_ip function family
///
/// This function can print IP address represented by std::string object,
/// string literal as `"192.168.1.1"` with null-terminated symbol, integral
/// type as `char`, `short`, `int`, `long` and etc, array of values of integral 
/// type, and container and tuple of same types elements
///
/// @author griha <gpgolikov@gmail.com>

#pragma once

#include <iostream>
#include <type_traits>

#include "type_traits.h"

namespace griha {

namespace details {

template <typename CharT, typename T>
std::basic_ostream<CharT>& 
print_ip_first_part(std::basic_ostream<CharT>& os, const T& value) {
    if constexpr (std::is_integral_v<T>)
        os << std::char_traits<CharT>::to_int_type(value);
    else
        os << value;
    return os;
}

template <typename CharT, typename T>
std::basic_ostream<CharT>& 
print_ip_part(std::basic_ostream<CharT>& os, const T& value) {
    os << '.';
    return print_ip_first_part(os, value);
}

template <typename CharT, typename It>
std::basic_ostream<CharT>& 
print_ip(std::basic_ostream<CharT>& os, It f, It l) {

    if (f == l)
        return os;

    print_ip_first_part(os, *f);
    for (++f; f != l; ++f) {
        print_ip_part(os, *f);
    }
        
    return os;
}

template <size_t I, typename CharT, typename... Args>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    if constexpr (I == sizeof...(Args))
        return os;
    else {
        print_ip_part(os, std::get<I>(ip));
        return print_ip<I + 1>(os, ip);
    }
}

template <typename CharT, typename... Args>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    static_assert(sizeof...(Args) > 0ul, "ip should contain at least one element");

    print_ip_first_part(os, std::get<0ul>(ip));
    return print_ip<1ul>(os, ip);
}

} // namespace details

template <typename CharT>
std::basic_ostream<CharT>& 
print_ip(std::basic_ostream<CharT>& os, const std::basic_string<CharT>& ip) {
    return os << ip;
}

template <typename CharT, typename CharT2, size_t N>
std::enable_if_t<
    is_character_v<CharT2>,
    std::basic_ostream<CharT>&
    >
print_ip(std::basic_ostream<CharT>& os, CharT2 (&ip)[N]) {
    std::copy_n(std::begin(ip), N - 1, std::ostream_iterator<CharT2>(os, ""));
    return os;
}

template <typename CharT, typename IntT, size_t N>
std::enable_if_t<
    !is_character_v<IntT>,
    std::basic_ostream<CharT>&
    >
print_ip(std::basic_ostream<CharT>& os, IntT (&ip)[N]) {
    return details::print_ip(os, std::begin(ip), std::end(ip));
}

template <typename CharT, typename IntT>
std::enable_if_t<
    std::is_integral_v<IntT>, 
    std::basic_ostream<CharT>&
    >
print_ip(std::basic_ostream<CharT>& os, IntT ip) {
    uint8_t arr[sizeof(IntT)];
    memcpy(arr, reinterpret_cast<uint8_t*>(&ip), sizeof(IntT));
    return details::print_ip(os, std::rbegin(arr), std::rend(arr));
}

template <typename CharT, typename ContT>
std::enable_if_t<
    std::is_same_v<
        decltype(std::declval<ContT>().begin()),
        decltype(std::declval<ContT>().end())
        >,
    std::basic_ostream<CharT>&
    >
print_ip(std::basic_ostream<CharT>& os, const ContT& ip) {
    return details::print_ip(os, ip.begin(), ip.end());
}

template <typename CharT, typename T>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::initializer_list<T>& ip) {
    return details::print_ip(os, ip.begin(), ip.end());
}

template <typename CharT, typename... Args>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    static_assert(is_all_same_v<Args...>, "all types of tuple should be equal");
    return details::print_ip(os, ip);
}

} // namespace griha