#include <array>
#include <string>
//==================================================================================================
template<typename Char>
//==================================================================================================
static const Char SECRET = 0x063248;
//==================================================================================================
template<typename Char, typename std::basic_string<Char>::size_type Length>
//==================================================================================================
struct obfuscated_string
{
    using String = std::basic_string<Char>;

    const std::array<const Char, Length> storage;

    operator String() const
    {
        String s{storage.data(), Length};
        for (auto& c: s)
            c ^= SECRET<Char>;
        return s;
    }
};
//==================================================================================================
template<typename ctype, ctype...STR>
//==================================================================================================
constexpr obfuscated_string<ctype, sizeof... (STR)> operator ""_hidden()
{
    return { { (STR ^ SECRET<ctype>)... } };
}
//==================================================================================================