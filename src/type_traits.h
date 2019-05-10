#pragma once

#include <type_traits>

namespace griha {

template <typename T, typename... Args>
struct is_one_of;

template <typename T>
struct is_one_of<T> : std::false_type {};

template <typename T, typename... Args>
struct is_one_of<T, T, Args...> : std::true_type {};

template <typename T, typename U, typename... Args>
struct is_one_of<T, U, Args...> : is_one_of<U, Args...> {};

template <typename T, typename... Args>
constexpr auto is_one_of_v = is_one_of<T, Args...>::value;

//---------

template <typename... Args>
struct is_all_same;

template <typename T>
struct is_all_same <T> : std::true_type { } ;

template <typename T>
struct is_all_same <T, T> : std::true_type { } ;

template<typename T, typename U, typename... Args>
struct is_all_same<T, U, Args...> : std::false_type {};

template <typename T, typename... Args>
struct is_all_same<T, T, Args...> : is_all_same<T, Args...> {};

template <typename... Args>
constexpr auto is_all_same_v = is_all_same<Args...>::value;

//------------

template <typename T>
constexpr auto is_character_v = is_one_of_v<std::decay_t<T>, char, wchar_t, char16_t, char32_t>;

} // namespace griha