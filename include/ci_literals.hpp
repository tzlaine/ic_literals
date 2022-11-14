#include <type_traits>
#include <limits>


namespace ci_literals {
  using namespace std;

#if !defined(__cpp_lib_constexpr_charconv)
  using longest_unsigned_type = // exposition only (and not proposed)
    conditional<sizeof(size_t) < sizeof(unsigned long long), unsigned long long, size_t>;

  constexpr int to_int(char c) // exposition only (and not proposed)
  {
      int result = 0;

      if (c >= 'A' && c <= 'F') {
        result = static_cast<int>(c) - static_cast<int>('A') + 10;
      } else if (c >= 'a' && c <= 'f') {
        result = static_cast<int>(c) - static_cast<int>('a') + 10;
      } else {
        result = static_cast<int>(c) - static_cast<int>('0');
      } else {
        throw logic_error("");
      }

      return result;
  }
#endif

  template<typename TargetType, size_t N>
  constexpr TargetType parse_ci(const char (&arr)[N]) // exposition only
  {
      int base = 10;
      int offset = 0;

      if (arr[0] == '0') {
        if (2 < N) {
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
        } else if (N == 2) {
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
      const auto result = std::from_chars(f, l, x, base);
      if (result.ptr != l || result.ec != errc{}) {
        throw logic_error("");
      }
      return x;
#else
      // Approximate implementation to work around the lack of a constexpr
      // from_chars() at the time of writing.
      longest_unsigned_type number = 0;
      longest_unsigned_type multiplier = 1;
      for (size_t i = 0; i < N - offset; ++i) {
        char c = arr[N - 1 - i];
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
        throw logic_error("");
      }
      return number;
#endif
  }

  // (signed) int
  template <char ...chars>
  constexpr auto operator"" c()
  {
    auto const x = parse_ci<int, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

#if 0
  // unsigned int
  template <char ...chars>
  constexpr auto operator"" uc()
  {
    auto const x = parse_ci<unsigned int, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Uc()
  {
    auto const x = parse_ci<unsigned int, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // (signed) long int
  template <char ...chars>
  constexpr auto operator"" lc()
  {
    auto const x = parse_ci<long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Lc()
  {
    auto const x = parse_ci<long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // unsigned long int
  template <char ...chars>
  constexpr auto operator"" luc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ulc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Ulc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" lUc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Luc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" uLc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ULc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LUc()
  {
    auto const x = parse_ci<unsigned long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // (signed) long long int
  template <char ...chars>
  constexpr auto operator"" llc()
  {
    auto const x = parse_ci<long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLc()
  {
    auto const x = parse_ci<long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }

  // unsigned long long int
  template <char ...chars>
  constexpr auto operator"" lluc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ullc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" Ullc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" llUc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLuc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" uLLc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" ULLc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
  template <char ...chars>
  constexpr auto operator"" LLUc()
  {
    auto const x = parse_ci<unsigned long long, sizeof...(chars)>({chars...});
    return integral_constant<decltype(x), x>{};
  }
#endif
}
