//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Written by Colin Finck for ENLYZE GmbH
//

#include "EnlyzeWinStringLib.h"

#include <converter.h>

// Conversion table for Windows-1252 characters 128..=159, which don't map exactly to Unicode codepoints.
const utf16_t SpecialEncodings[32] = {
    0x20AC, 0xFFFD, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0xFFFD, 0x017D, 0xFFFD,
    0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0xFFFD, 0x017E, 0x0178
};


// Convert a Windows-1252 std::string to a UTF-8 std::string.
std::string
Str1252ToStr(const std::string& str1252)
{
    // A UTF-8 character needs up to 3 codepoints for a single Windows-1252 character.
    std::string str(str1252.size() * 3, '\0');
    utf8_t* pOutput = reinterpret_cast<utf8_t*>(str.data());
    size_t i = 0;

    for (const uint8_t* pWalk = reinterpret_cast<const uint8_t*>(str1252.c_str()); *pWalk != 0; pWalk++)
    {
        if (*pWalk < 128)
        {
            // Windows-1252 characters 0..=127 map directly to UTF-8 codepoints.
            pOutput[i] = *pWalk;
            i++;
        }
        else if (*pWalk < 160)
        {
            // Windows-1252 characters 128..=159 follow no pattern and their Unicode character IDs need to be encoded as UTF-8.
            i += encode_utf8(SpecialEncodings[*pWalk - 128], pOutput, str.size(), i);
        }
        else
        {
            // Windows-1252 characters 160..=255 map directly to the same Unicode character IDs, which need to be encoded as UTF-8.
            i += encode_utf8(*pWalk, pOutput, str.size(), i);
        }
    }

    return str;
}

// Convert a Windows-1252 std::string to a UTF-16 std::wstring.
std::wstring
Str1252ToWstr(const std::string& str1252)
{
    // A UTF-16 character always needs a single codepoint for a Windows-1252 character.
    std::wstring wstr(str1252.size(), L'\0');
    utf16_t* pOutput = reinterpret_cast<utf16_t*>(wstr.data());
    size_t i = 0;

    for (const uint8_t* pWalk = reinterpret_cast<const uint8_t*>(str1252.c_str()); *pWalk != 0; pWalk++)
    {
        if (*pWalk >= 128 && *pWalk < 160)
        {
            // Windows-1252 characters 128..=159 follow no pattern and need a special mapping.
            pOutput[i] = SpecialEncodings[*pWalk - 128];
        }
        else
        {
            // All other characters map directly to UTF-16 codepoints.
            pOutput[i] = *pWalk;
        }

        i++;
    }

    return wstr;
}
