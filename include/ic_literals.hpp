#include <boost/hana.hpp>

#include <algorithm>
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

  // Everything guarded by this macro is exposition only (and not proposed).
#if !defined(__cpp_lib_constexpr_charconv)
  using longest_unsigned_type =
      conditional_t<
          sizeof(size_t) < sizeof(unsigned long long),
          unsigned long long,
          size_t>;

  template<char C>
  constexpr auto to_int()
  {
      if constexpr ('A' <= C && C <= 'F') {
        return boost::hana::llong_c<C - 'A' + 10>;
      } else if constexpr ('a' <= C && C <= 'f') {
        return boost::hana::llong_c<C - 'a' + 10>;
      } else {
        return boost::hana::llong_c<C - '0'>;
      }
  }
#endif

  struct ic_base_and_offset_result
  {
    int base;
    int offset;
  };

  template<size_t Size, char... Chars>
  constexpr ic_base_and_offset_result ic_base_and_offset()
  {
      constexpr char arr[] = {Chars...};
      if constexpr (arr[0] == '0' && 2 < Size) {
        constexpr bool is_hex = arr[1] == 'x' || arr[1] == 'X';
        constexpr bool is_binary = arr[1] == 'b';

        if constexpr (is_hex)
          return {16, 2};
        else if constexpr (is_binary)
          return {2, 2};
        else
          return {8, 1};
      }
      return {10, 0};
  }

  template<typename TargetType, char ...Chars>
  constexpr TargetType ic_parse() // exposition only
  {
      constexpr auto size = sizeof...(Chars);

      constexpr auto bao = ic_base_and_offset<size, Chars...>();
      constexpr int base = bao.base;
      constexpr int offset = bao.offset;

#if defined(__cpp_lib_constexpr_charconv)
      // This is really here just for documentation purposes right now,
      // because this is what is proposed in the paper.  No implementation has
      // constexpr from_chars() at the time of this writing.
      const auto f = std::begin(arr) + offset, l = std::end(arr);
      TargetType x{};
      constexpr auto result = from_chars(f, l, x, base);
      return result.ptr == l && result.ec == errc{} ? x : throw logic_error("");
#else
      // Approximate implementation to work around the lack of a constexpr
      // from_chars() at the time of writing.

      using namespace boost::hana::literals;

      constexpr auto digits_ = boost::hana::make_tuple(to_int<Chars>()...);
      constexpr auto digits_trimmed =
          boost::hana::drop_front(digits_, boost::hana::llong_c<offset>);

      // initial is (result, mulitplier)
      constexpr auto initial = boost::hana::make_tuple(
          boost::hana::llong_c<0>, boost::hana::llong_c<1>);
      constexpr auto final = boost::hana::reverse_fold(
          digits_trimmed, initial, [base](auto state, auto element_) {
              constexpr auto result = boost::hana::llong_c<state[0_c].value>;
              constexpr auto multiplier = boost::hana::llong_c<state[1_c].value>;
              constexpr auto element = boost::hana::llong_c<element_.value>;
              static_assert(
                  element * multiplier / multiplier == element,
                  "Overflow detected");
              static_assert(
                  result + element * multiplier - element * multiplier ==
                      result,
                  "Overflow detected");
              static_assert(
                  multiplier * base / base == multiplier, "Overflow detected");
              return boost::hana::make_tuple(
                  boost::hana::llong_c<result + element * multiplier>,
                  boost::hana::llong_c<multiplier * base>);
          });

      constexpr auto retval = final[0_c].value;
      static_assert(
          retval <= std::numeric_limits<TargetType>::max(),
          "The number parsed in an integral_constant literal is out of the "
          "representable range for the integral type being parsed");
      return retval;
#endif
  }

  // (signed) int
  template <char ...Chars>
  constexpr auto operator"" ic()
  {
    constexpr auto x = ic_parse<int, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // unsigned
  template <char ...Chars>
  constexpr auto operator"" uic()
  {
    constexpr auto x = ic_parse<unsigned, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Uic()
  {
    constexpr auto x = ic_parse<unsigned, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // (signed) long
  template <char ...Chars>
  constexpr auto operator"" lic()
  {
    constexpr auto x = ic_parse<long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Lic()
  {
    constexpr auto x = ic_parse<long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // unsigned long
  template <char ...Chars>
  constexpr auto operator"" luic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" ulic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Ulic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" lUic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Luic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" uLic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" ULic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" LUic()
  {
    constexpr auto x = ic_parse<unsigned long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // (signed) long long
  template <char ...Chars>
  constexpr auto operator"" llic()
  {
    constexpr auto x = ic_parse<long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" LLic()
  {
    constexpr auto x = ic_parse<long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // unsigned long long
  template <char ...Chars>
  constexpr auto operator"" lluic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" ullic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Ullic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" llUic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" LLuic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" uLLic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" ULLic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" LLUic()
  {
    constexpr auto x = ic_parse<unsigned long long, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // ptrdiff_t
  template <char ...Chars>
  constexpr auto operator"" zic()
  {
    constexpr auto x = ic_parse<ptrdiff_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Zic()
  {
    constexpr auto x = ic_parse<ptrdiff_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }

  // size_t
  template <char ...Chars>
  constexpr auto operator"" zuic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" uzic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Uzic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" zUic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" Zuic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" uZic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" UZic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
  template <char ...Chars>
  constexpr auto operator"" ZUic()
  {
    constexpr auto x = ic_parse<size_t, Chars...>();
    return integral_constant<remove_const_t<decltype(x)>, x>{};
  }
}
