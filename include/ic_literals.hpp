#include <cassert>
#include <stdexcept>
#include <limits>
#include <type_traits>


namespace std {
    template<typename T, T V>
    constexpr auto operator-(integral_constant<T, V>)
        -> integral_constant<T, -V>
    {
        return {};
    }
}

namespace ic_literals {
  using namespace std;

#if !defined(__cpp_lib_constexpr_charconv)
  using longest_unsigned_type = // exposition only (and not proposed)
      conditional_t<
          sizeof(size_t) < sizeof(unsigned long long),
          unsigned long long,
          size_t>;

  constexpr int to_int(char c) // exposition only (and not proposed)
  {
      int result = 0;

      if (c >= 'A' && c <= 'F') {
        result = static_cast<int>(c) - static_cast<int>('A') + 10;
      } else if (c >= 'a' && c <= 'f') {
        result = static_cast<int>(c) - static_cast<int>('a') + 10;
      } else if (c >= '0' && c <= '9') {
        result = static_cast<int>(c) - static_cast<int>('0');
      } else {
          throw logic_error("");
      }

      return result;
  }
#endif

  template<typename TargetType, char ...chars>
  constexpr TargetType parse_ci() // exposition only
  {
      int base = 10;
      int offset = 0;

      constexpr char arr[] = {chars...};
      constexpr auto size = sizeof...(chars);

      if (arr[0] == '0') {
        if (2 < size) {
          const bool is_hex = arr[1] == 'x' || arr[1] == 'X';
          const bool is_binary = arr[1] == 'b';
  
          if (is_hex) {
            base = 16;
            offset = 2;
          } else if (is_binary) {
            base = 2;
            offset = 2;
          } else {
            base = 8;
            offset = 1;
          }
        } else if (size == 2) {
          base = 8;
          offset = 1;
        }
      }

#if defined(__cpp_lib_constexpr_charconv)
      // This is really here just for documentation purposes right now,
      // because this is what is proposed in the paper.  No implementation has
      // constexpr from_chars() at the time of this writing.
      const auto f = std::begin(arr) + offset, l = std::end(arr);
      TargetType x{};
      constexpr auto result = std::from_chars(f, l, x, base);
      if (result.ptr != l || result.ec != errc{}) {
        throw logic_error("");
      }
      return x;
#else
      // Approximate implementation to work around the lack of a constexpr
      // from_chars() at the time of writing.
      longest_unsigned_type number = 0;
      longest_unsigned_type multiplier = 1;
      for (size_t i = 0; i < size - offset; ++i) {
        char c = arr[size - 1 - i];
        longest_unsigned_type digit_value = to_int(c);
        // TODO: Check for overflow in the multiplication below
        longest_unsigned_type digit_value_here = digit_value * multiplier;
        // TODO: Check for overflow in the addition below
        number += digit_value_here;
        // TODO: Check for overflow in the multiplication below
        multiplier *= base;
      }
      if (number < (longest_unsigned_type)std::numeric_limits<TargetType>::min() ||
          (longest_unsigned_type)std::numeric_limits<TargetType>::max() < number) {
          // TODO: We should fail here, a la throw logic_error(""), but the
          // predicate to this if is not a constant epxression.
      }
      return number;
#endif
  }

  // (signed) int
  template <char ...chars>
  constexpr auto operator"" ic()
  {
    constexpr auto x = parse_ci<int, chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // unsigned int
  template <char ...chars>
  constexpr auto operator"" uic()
  {
    constexpr auto x = parse_ci<unsigned int, chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Uic()
  {
    constexpr auto x = parse_ci<unsigned int, chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // (signed) long int
  template <char ...chars>
  constexpr auto operator"" lic()
  {
    auto const x = parse_ci<long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Lic()
  {
    auto const x = parse_ci<long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // unsigned long int
  template <char ...chars>
  constexpr auto operator"" luic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ulic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Ulic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" lUic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Luic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" uLic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ULic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LUic()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // (signed) long long int
  template <char ...chars>
  constexpr auto operator"" llic()
  {
    auto const x = parse_ci<long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLic()
  {
    auto const x = parse_ci<long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // unsigned long long int
  template <char ...chars>
  constexpr auto operator"" lluic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ullic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Ullic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" llUic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLuic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" uLLic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ULLic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLUic()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

    // TODO: zic, uzic
}
