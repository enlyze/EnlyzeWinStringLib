//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Written by Colin Finck for ENLYZE GmbH
//

#include "EnlyzeWinStringLib.h"

extern "C" unsigned int __stdcall SysStringLen(const wchar_t* pbstr);


static size_t
_BstrLength(const wchar_t* bstr)
{
    // A BSTR may be NULL and must then be treated like an empty string.
    // See https://blogs.msdn.microsoft.com/ericlippert/2003/09/12/erics-complete-guide-to-bstr-semantics/
    if (!bstr)
    {
        return 0;
    }

    // BSTRs are always prefixed with the length in characters that can be determined by SysStringLen.
    size_t MaxLen = SysStringLen(bstr);

    // However, the length above is only the maximum size of the buffer and not necessarily the actual
    // string length. An embedded NUL character inside the buffer may end the string prematurely.
    // While most guides state that BSTRs are always NUL-terminated, let's be on the absolute safe side
    // here and only look for a NUL terminator up to the maximum string length.
    size_t cch;
    for (cch = 0; cch < MaxLen; cch++)
    {
        if (bstr[cch] == L'\0')
        {
            break;
        }
    }

    return cch;
}

// Convert a UTF-16 BSTR to a UTF-8 std::string.
std::string
BstrToStr(const wchar_t* bstr)
{
    size_t cch = _BstrLength(bstr);
    return WcharSizedToStr(bstr, cch);
}

// Convert a UTF-16 BSTR to a UTF-16 std::wstring.
std::wstring
BstrToWstr(const wchar_t* bstr)
{
    size_t cch = _BstrLength(bstr);
    return std::wstring(bstr, cch);
}
