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

template <typename FwdIt, typename CharT>
std::basic_ostream<CharT>& print_ip(std::basic_ostream<CharT>& os,
                                    FwdIt f, FwdIt l) {
    using char_traits = std::char_traits<CharT>;
    constexpr CharT delim[] = {char_traits::to_char_type('.'), 0};
    if (f == l)
        return os;

    auto pl = std::prev(l);
    std::copy(f, pl, std::ostream_iterator<typename char_traits::int_type, CharT>(os, delim));
    os << char_traits::to_int_type(*pl);
        
    return os;
}

template <size_t I, typename CharT, typename... Args>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    if constexpr (I == sizeof...(Args))
        return os;
    else {
        os << '.' << std::char_traits<CharT>::to_int_type(std::get<I>(ip));
        return print_ip<I + 1>(os, ip);
    }
}

template <typename CharT, typename... Args>
std::basic_ostream<CharT>&
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    static_assert(sizeof...(Args) > 0ul, "ip should contain at least one element");

    os << std::char_traits<CharT>::to_int_type(std::get<0ul>(ip));
    return print_ip<1ul>(os, ip);
}

} // namespace details

template <typename CharT>
std::basic_ostream<CharT>& print_ip(std::basic_ostream<CharT>& os,
                                    const std::basic_string<CharT>& ip) {
    return os << ip;
}

template <typename CharT, typename CharT2, size_t N>
std::enable_if_t<
    is_character_v<CharT2>,
    std::basic_ostream<CharT>&>
print_ip(std::basic_ostream<CharT>& os, CharT2 (&ip)[N]) {
    std::copy_n(std::cbegin(ip), N - 1, std::ostream_iterator<CharT2>(os, ""));
    return os;
}

template <typename CharT, typename IntT>
std::enable_if_t<
    std::is_integral_v<IntT>, 
    std::basic_ostream<CharT>&>
print_ip(std::basic_ostream<CharT>& os, IntT ip) {
    uint8_t arr[sizeof(IntT)];
    memcpy(arr, reinterpret_cast<uint8_t*>(&ip), sizeof(IntT));
    return details::print_ip(os, std::crbegin(arr), std::crend(arr));
}

template <typename CharT, typename IntT, size_t N>
std::enable_if_t<
    std::is_integral_v<IntT> && !is_character_v<IntT>,
    std::basic_ostream<CharT>&>
print_ip(std::basic_ostream<CharT>& os, IntT (&ip)[N]) {
    return details::print_ip(os, std::cbegin(ip), std::cend(ip));
}

template <typename CharT, typename ContT>
std::enable_if_t<
    std::is_member_function_pointer_v<decltype(&ContT::cbegin)> &&
        std::is_member_function_pointer_v<decltype(&ContT::cend)>,
    std::basic_ostream<CharT>&>
print_ip(std::basic_ostream<CharT>& os, const ContT& ip) {
    return details::print_ip(os, ip.cbegin(), ip.cend());
}

template <typename CharT, typename... Args>
std::enable_if_t<
    is_all_same_v<Args...>,
    std::basic_ostream<CharT>&>
print_ip(std::basic_ostream<CharT>& os, const std::tuple<Args...>& ip) {
    return details::print_ip(os, ip);
}

} // namespace griha