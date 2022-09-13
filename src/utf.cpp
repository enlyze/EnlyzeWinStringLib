//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Copyright (c) 2022 Colin Finck, ENLYZE GmbH <c.finck@enlyze.com>
// SPDX-License-Identifier: MIT
//

#include "EnlyzeWinStringLib.h"

#include <converter.h>


// Convert a UTF-8 NUL-terminated char buffer to a UTF-16 std::wstring.
std::wstring
CharToWstr(const char* psz)
{
    return CharSizedToWstr(psz, strlen(psz));
}

// Convert a UTF-8 char buffer with given size to a UTF-16 std::wstring.
std::wstring
CharSizedToWstr(const char* ps, size_t cch)
{
    // A UTF-16 string needs as many codepoints as the UTF-8 string, or fewer.
    std::wstring wstr(cch, L'\0');

    // Windows has strictly defined wchar_t to 2 bytes, so this conversion is safe.
    const utf8_t* pInput = reinterpret_cast<const utf8_t*>(ps);
    utf16_t* pOutput = reinterpret_cast<utf16_t*>(wstr.data());

    size_t cchOutput = utf8_to_utf16(pInput, cch, pOutput, wstr.size());
    wstr.resize(cchOutput);

    return wstr;
}

// Convert a UTF-8 std::string to a UTF-16 std::wstring.
std::wstring
StrToWstr(const std::string& str)
{
    return CharSizedToWstr(str.c_str(), str.size());
}

// Convert a UTF-16 NUL-terminated wchar_t buffer to a UTF-8 std::string.
std::string
WcharToStr(const wchar_t* pwsz)
{
    return WcharSizedToStr(pwsz, wcslen(pwsz));
}

// Convert a UTF-16 wchar_t buffer with given size to a UTF-8 std::string.
std::string
WcharSizedToStr(const wchar_t* pws, size_t cch)
{
    // A UTF-16 codepoint can map to 3 UTF-8 codepoints in the worst case.
    std::string str(cch * 3, '\0');

    // Windows has strictly defined wchar_t to 2 bytes, so this conversion is safe.
    const utf16_t* pInput = reinterpret_cast<const utf16_t*>(pws);
    utf8_t* pOutput = reinterpret_cast<utf8_t*>(str.data());

    size_t cchOutput = utf16_to_utf8(pInput, cch, pOutput, str.size());
    str.resize(cchOutput);

    return str;
}

// Convert a UTF-16 std::wstring to a UTF-8 std::string.
std::string
WstrToStr(const std::wstring& wstr)
{
    return WcharSizedToStr(wstr.c_str(), wstr.size());
}
