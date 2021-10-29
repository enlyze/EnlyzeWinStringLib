//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Written by Colin Finck for ENLYZE GmbH
//

#pragma once

#include <string>


// MSVC 2017 CRT's isspace() chokes on umlauts: https://developercommunity.visualstudio.com/content/problem/235300/universalcrt-incorrect-assert-in-isspace.html
// It also does way more than we want (taking locale into account), so implement our own function checking for spaces here.
// This one can be inlined by the compiler then :)
inline bool
IsSpaceCharacter(const char c)
{
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

inline void
StrLeftTrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const char c)
        {
            return !IsSpaceCharacter(c) && c != '\0';
        }));
}

inline void
StrRightTrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const char c)
        {
            return !IsSpaceCharacter(c) && c != '\0';
        }).base(), s.end());
}

inline void
StrTrim(std::string& s) {
    StrLeftTrim(s);
    StrRightTrim(s);
}
