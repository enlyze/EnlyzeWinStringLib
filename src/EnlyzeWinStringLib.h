//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Written by Colin Finck for ENLYZE GmbH
//

#pragma once

#include <optional>
#include <string>

#include "trim.h"

// This header is meant to be included by applications using the library, without any preconditions.
// Therefore, it must only include system headers that also have no preconditions (like header order, configuration via preprocessor defines, etc.).
//
// Unfortunately, this does not apply to <Windows.h>, which depends on the include order and is often configured via preprocessor defines
// (like #define _WIN32_WINNT).
// This is why all Bstr functions use the wchar_t* type here instead of the more appropriate BSTR typedef.
// You can just pass a BSTR though, it's fully compatible (albeit confusing).

// 1252.cpp
std::string Str1252ToStr(const std::string& str1252);
std::wstring Str1252ToWstr(const std::string& str1252);

// bstr.cpp
std::string BstrToStr(const wchar_t* bstr);
std::wstring BstrToWstr(const wchar_t* bstr);

// numeric.cpp
std::optional<long> StrToLong(const std::string& str);
std::optional<size_t> StrToSizeT(const std::string& str);

// utf.cpp
std::wstring CharToWstr(const char* psz);
std::wstring CharSizedToWstr(const char* ps, size_t cch);
std::wstring StrToWstr(const std::string& str);
std::string WcharToStr(const wchar_t* pwsz);
std::string WcharSizedToStr(const wchar_t* pws, size_t cch);
std::string WstrToStr(const std::wstring& wstr);
