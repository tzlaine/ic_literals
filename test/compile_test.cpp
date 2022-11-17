#include <ic_literals.hpp>

#include <string>
#include <type_traits>


int main() {
    using namespace ic_literals;

    // int
    static_assert(std::is_same_v<decltype(0ic), std::integral_constant<int, 0>>);
    static_assert(std::is_same_v<decltype(1ic), std::integral_constant<int, 1>>);
    static_assert(std::is_same_v<decltype(2ic), std::integral_constant<int, 2>>);
    static_assert(std::is_same_v<decltype(-1ic), std::integral_constant<int, -1>>);
    static_assert(std::is_same_v<decltype(0xaic), std::integral_constant<int, 10>>);

    // octal
    static_assert(std::is_same_v<decltype(00ic), std::integral_constant<int, 0>>);
    static_assert(std::is_same_v<decltype(01ic), std::integral_constant<int, 1>>);
    static_assert(std::is_same_v<decltype(02ic), std::integral_constant<int, 2>>);
    static_assert(std::is_same_v<decltype(-01ic), std::integral_constant<int, -1>>);
    static_assert(std::is_same_v<decltype(012ic), std::integral_constant<int, 10>>);

    // binary
    static_assert(std::is_same_v<decltype(0b0ic), std::integral_constant<int, 0>>);
    static_assert(std::is_same_v<decltype(0b1ic), std::integral_constant<int, 1>>);
    static_assert(std::is_same_v<decltype(0b10ic), std::integral_constant<int, 2>>);
    static_assert(std::is_same_v<decltype(-0b1ic), std::integral_constant<int, -1>>);
    static_assert(std::is_same_v<decltype(0b1010ic), std::integral_constant<int, 10>>);

    // hex
    static_assert(std::is_same_v<decltype(0x0ic), std::integral_constant<int, 0>>);
    static_assert(std::is_same_v<decltype(0x1ic), std::integral_constant<int, 1>>);
    static_assert(std::is_same_v<decltype(0x2ic), std::integral_constant<int, 2>>);
    static_assert(std::is_same_v<decltype(-0x1ic), std::integral_constant<int, -1>>);
    static_assert(std::is_same_v<decltype(0xaic), std::integral_constant<int, 10>>);
    static_assert(std::is_same_v<decltype(0Xaic), std::integral_constant<int, 10>>);
    static_assert(std::is_same_v<decltype(0xAic), std::integral_constant<int, 10>>);
    static_assert(std::is_same_v<decltype(0XAic), std::integral_constant<int, 10>>);

    // TODO: Note in the proposal that we can't have the much nicer "c" UDT
    // without giving up support for hex literals.

#if 0 // This fails!  TODO: Note this limitation in the proposal.
    // INT_MIN
    static_assert(std::is_same_v<
                  decltype(-2147483648ic),
                  std::integral_constant<int, -2147483648>>);
#endif
    // INT_MIN + 1
    static_assert(std::is_same_v<
                  decltype(-2147483647ic),
                  std::integral_constant<int, -2147483647>>);

    // INT_MAX
    static_assert(std::is_same_v<
                  decltype(2147483647ic),
                  std::integral_constant<int, 2147483647>>);

    // unsigned int
    static_assert(std::is_same_v<
                  decltype(0uic),
                  std::integral_constant<unsigned int, 0u>>);
    static_assert(std::is_same_v<
                  decltype(42uic),
                  std::integral_constant<unsigned int, 42u>>);
    static_assert(std::is_same_v<
                  decltype(-1uic),
                  std::integral_constant<unsigned int, -1u>>);

    static_assert(std::is_same_v<
                  decltype(0Uic),
                  std::integral_constant<unsigned int, 0U>>);
    static_assert(std::is_same_v<
                  decltype(42Uic),
                  std::integral_constant<unsigned int, 42U>>);
    static_assert(std::is_same_v<
                  decltype(-1Uic),
                  std::integral_constant<unsigned int, -1U>>);

    // long
    static_assert(
        std::is_same_v<decltype(0lic), std::integral_constant<long int, 0l>>);
    static_assert(
        std::is_same_v<decltype(42lic), std::integral_constant<long int, 42l>>);
    static_assert(
        std::is_same_v<decltype(-1lic), std::integral_constant<long int, -1l>>);

    static_assert(
        std::is_same_v<decltype(0Lic), std::integral_constant<long int, 0L>>);
    static_assert(
        std::is_same_v<decltype(42Lic), std::integral_constant<long int, 42L>>);
    static_assert(
        std::is_same_v<decltype(-1Lic), std::integral_constant<long int, -1L>>);

    // unsigned long
    static_assert(std::is_same_v<
                  decltype(0ulic),
                  std::integral_constant<unsigned long, 0ul>>);
    static_assert(std::is_same_v<
                  decltype(42ulic),
                  std::integral_constant<unsigned long, 42ul>>);
    static_assert(std::is_same_v<
                  decltype(-1ulic),
                  std::integral_constant<unsigned long, -1ul>>);
    static_assert(std::is_same_v<
                  decltype(0luic),
                  std::integral_constant<unsigned long, 0lu>>);
    static_assert(std::is_same_v<
                  decltype(42luic),
                  std::integral_constant<unsigned long, 42lu>>);
    static_assert(std::is_same_v<
                  decltype(-1luic),
                  std::integral_constant<unsigned long, -1lu>>);

    static_assert(std::is_same_v<
                  decltype(0Ulic),
                  std::integral_constant<unsigned long, 0Ul>>);
    static_assert(std::is_same_v<
                  decltype(42Ulic),
                  std::integral_constant<unsigned long, 42Ul>>);
    static_assert(std::is_same_v<
                  decltype(-1Ulic),
                  std::integral_constant<unsigned long, -1Ul>>);
    static_assert(std::is_same_v<
                  decltype(0lUic),
                  std::integral_constant<unsigned long, 0lU>>);
    static_assert(std::is_same_v<
                  decltype(42lUic),
                  std::integral_constant<unsigned long, 42lU>>);
    static_assert(std::is_same_v<
                  decltype(-1lUic),
                  std::integral_constant<unsigned long, -1lU>>);

    static_assert(std::is_same_v<
                  decltype(0uLic),
                  std::integral_constant<unsigned long, 0uL>>);
    static_assert(std::is_same_v<
                  decltype(42uLic),
                  std::integral_constant<unsigned long, 42uL>>);
    static_assert(std::is_same_v<
                  decltype(-1uLic),
                  std::integral_constant<unsigned long, -1uL>>);
    static_assert(std::is_same_v<
                  decltype(0Luic),
                  std::integral_constant<unsigned long, 0Lu>>);
    static_assert(std::is_same_v<
                  decltype(42Luic),
                  std::integral_constant<unsigned long, 42Lu>>);
    static_assert(std::is_same_v<
                  decltype(-1Luic),
                  std::integral_constant<unsigned long, -1Lu>>);

    static_assert(std::is_same_v<
                  decltype(0ULic),
                  std::integral_constant<unsigned long, 0UL>>);
    static_assert(std::is_same_v<
                  decltype(42ULic),
                  std::integral_constant<unsigned long, 42UL>>);
    static_assert(std::is_same_v<
                  decltype(-1ULic),
                  std::integral_constant<unsigned long, -1UL>>);
    static_assert(std::is_same_v<
                  decltype(0LUic),
                  std::integral_constant<unsigned long, 0LU>>);
    static_assert(std::is_same_v<
                  decltype(42LUic),
                  std::integral_constant<unsigned long, 42LU>>);
    static_assert(std::is_same_v<
                  decltype(-1LUic),
                  std::integral_constant<unsigned long, -1LU>>);

    // long long
    static_assert(
        std::is_same_v<decltype(0llic), std::integral_constant<long long, 0ll>>);
    static_assert(
        std::is_same_v<decltype(42llic), std::integral_constant<long long, 42ll>>);
    static_assert(
        std::is_same_v<decltype(-1llic), std::integral_constant<long long, -1ll>>);

    static_assert(
        std::is_same_v<decltype(0LLic), std::integral_constant<long long, 0LL>>);
    static_assert(
        std::is_same_v<decltype(42LLic), std::integral_constant<long long, 42LL>>);
    static_assert(
        std::is_same_v<decltype(-1LLic), std::integral_constant<long long, -1LL>>);

    // unsigned long long
    static_assert(std::is_same_v<
                  decltype(0ullic),
                  std::integral_constant<unsigned long long, 0ull>>);
    static_assert(std::is_same_v<
                  decltype(42ullic),
                  std::integral_constant<unsigned long long, 42ull>>);
    static_assert(std::is_same_v<
                  decltype(-1ullic),
                  std::integral_constant<unsigned long long, -1ull>>);
    static_assert(std::is_same_v<
                  decltype(0lluic),
                  std::integral_constant<unsigned long long, 0llu>>);
    static_assert(std::is_same_v<
                  decltype(42lluic),
                  std::integral_constant<unsigned long long, 42llu>>);
    static_assert(std::is_same_v<
                  decltype(-1lluic),
                  std::integral_constant<unsigned long long, -1llu>>);

    static_assert(std::is_same_v<
                  decltype(0Ullic),
                  std::integral_constant<unsigned long long, 0Ull>>);
    static_assert(std::is_same_v<
                  decltype(42Ullic),
                  std::integral_constant<unsigned long long, 42Ull>>);
    static_assert(std::is_same_v<
                  decltype(-1Ullic),
                  std::integral_constant<unsigned long long, -1Ull>>);
    static_assert(std::is_same_v<
                  decltype(0llUic),
                  std::integral_constant<unsigned long long, 0llU>>);
    static_assert(std::is_same_v<
                  decltype(42llUic),
                  std::integral_constant<unsigned long long, 42llU>>);
    static_assert(std::is_same_v<
                  decltype(-1llUic),
                  std::integral_constant<unsigned long long, -1llU>>);

    static_assert(std::is_same_v<
                  decltype(0uLLic),
                  std::integral_constant<unsigned long long, 0uLL>>);
    static_assert(std::is_same_v<
                  decltype(42uLLic),
                  std::integral_constant<unsigned long long, 42uLL>>);
    static_assert(std::is_same_v<
                  decltype(-1uLLic),
                  std::integral_constant<unsigned long long, -1uLL>>);
    static_assert(std::is_same_v<
                  decltype(0LLuic),
                  std::integral_constant<unsigned long long, 0LLu>>);
    static_assert(std::is_same_v<
                  decltype(42LLuic),
                  std::integral_constant<unsigned long long, 42LLu>>);
    static_assert(std::is_same_v<
                  decltype(-1LLuic),
                  std::integral_constant<unsigned long long, -1LLu>>);

    static_assert(std::is_same_v<
                  decltype(0ULLic),
                  std::integral_constant<unsigned long long, 0ULL>>);
    static_assert(std::is_same_v<
                  decltype(42ULLic),
                  std::integral_constant<unsigned long long, 42ULL>>);
    static_assert(std::is_same_v<
                  decltype(-1ULLic),
                  std::integral_constant<unsigned long long, -1ULL>>);
    static_assert(std::is_same_v<
                  decltype(0LLUic),
                  std::integral_constant<unsigned long long, 0LLU>>);
    static_assert(std::is_same_v<
                  decltype(42LLUic),
                  std::integral_constant<unsigned long long, 42LLU>>);
    static_assert(std::is_same_v<
                  decltype(-1LLUic),
                  std::integral_constant<unsigned long long, -1LLU>>);

    // ptrdiff_t
    static_assert(
        std::is_same_v<decltype(0zic), std::integral_constant<ptrdiff_t, 0z>>);
    static_assert(
        std::is_same_v<decltype(42zic), std::integral_constant<ptrdiff_t, 42z>>);
    static_assert(
        std::is_same_v<decltype(-1zic), std::integral_constant<ptrdiff_t, -1z>>);

    static_assert(
        std::is_same_v<decltype(0Zic), std::integral_constant<ptrdiff_t, 0Z>>);
    static_assert(
        std::is_same_v<decltype(42Zic), std::integral_constant<ptrdiff_t, 42Z>>);
    static_assert(
        std::is_same_v<decltype(-1Zic), std::integral_constant<ptrdiff_t, -1Z>>);

    // size_t
    static_assert(std::is_same_v<
                  decltype(0uzic),
                  std::integral_constant<size_t, 0uz>>);
    static_assert(std::is_same_v<
                  decltype(42uzic),
                  std::integral_constant<size_t, 42uz>>);
    static_assert(std::is_same_v<
                  decltype(-1uzic),
                  std::integral_constant<size_t, -1uz>>);
    static_assert(std::is_same_v<
                  decltype(0zuic),
                  std::integral_constant<size_t, 0zu>>);
    static_assert(std::is_same_v<
                  decltype(42zuic),
                  std::integral_constant<size_t, 42zu>>);
    static_assert(std::is_same_v<
                  decltype(-1zuic),
                  std::integral_constant<size_t, -1zu>>);

    static_assert(std::is_same_v<
                  decltype(0Uzic),
                  std::integral_constant<size_t, 0Uz>>);
    static_assert(std::is_same_v<
                  decltype(42Uzic),
                  std::integral_constant<size_t, 42Uz>>);
    static_assert(std::is_same_v<
                  decltype(-1Uzic),
                  std::integral_constant<size_t, -1Uz>>);
    static_assert(std::is_same_v<
                  decltype(0zUic),
                  std::integral_constant<size_t, 0zU>>);
    static_assert(std::is_same_v<
                  decltype(42zUic),
                  std::integral_constant<size_t, 42zU>>);
    static_assert(std::is_same_v<
                  decltype(-1zUic),
                  std::integral_constant<size_t, -1zU>>);

    static_assert(std::is_same_v<
                  decltype(0uZic),
                  std::integral_constant<size_t, 0uZ>>);
    static_assert(std::is_same_v<
                  decltype(42uZic),
                  std::integral_constant<size_t, 42uZ>>);
    static_assert(std::is_same_v<
                  decltype(-1uZic),
                  std::integral_constant<size_t, -1uZ>>);
    static_assert(std::is_same_v<
                  decltype(0Zuic),
                  std::integral_constant<size_t, 0Zu>>);
    static_assert(std::is_same_v<
                  decltype(42Zuic),
                  std::integral_constant<size_t, 42Zu>>);
    static_assert(std::is_same_v<
                  decltype(-1Zuic),
                  std::integral_constant<size_t, -1Zu>>);

    static_assert(std::is_same_v<
                  decltype(0UZic),
                  std::integral_constant<size_t, 0UZ>>);
    static_assert(std::is_same_v<
                  decltype(42UZic),
                  std::integral_constant<size_t, 42UZ>>);
    static_assert(std::is_same_v<
                  decltype(-1UZic),
                  std::integral_constant<size_t, -1UZ>>);
    static_assert(std::is_same_v<
                  decltype(0ZUic),
                  std::integral_constant<size_t, 0ZU>>);
    static_assert(std::is_same_v<
                  decltype(42ZUic),
                  std::integral_constant<size_t, 42ZU>>);
    static_assert(std::is_same_v<
                  decltype(-1ZUic),
                  std::integral_constant<size_t, -1ZU>>);
}
