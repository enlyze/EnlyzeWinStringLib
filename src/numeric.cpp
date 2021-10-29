//
// EnlyzeWinStringLib - A self-contained exception-less static library of string and character set conversion functions (for Windows NT 4.0 and above)
// Written by Colin Finck for ENLYZE GmbH
//

#include "EnlyzeWinStringLib.h"

#include <cstdlib>


// Convert a fully numeric std::string to size_t.
// Needed to encapsulate the difficult semantics of strtol (and because std::stoi may throw an exception).
std::optional<long>
StrToLong(const std::string& str)
{
    char* pszEnd;
    long Value = strtol(str.c_str(), &pszEnd, 10);

    if (errno != ERANGE && *pszEnd == '\0')
    {
        // The entire string was numeric and converted successfully.
        return Value;
    }

    // Indicate a conversion error.
    return std::optional<long>();
}

// Convert a fully numeric std::string to size_t.
// Needed to encapsulate the difficult semantics of strtoul (and because std::stoi may throw an exception).
std::optional<size_t>
StrToSizeT(const std::string& str)
{
    char* pszEnd;
    size_t Value = strtoul(str.c_str(), &pszEnd, 10);

    if (errno != ERANGE && *pszEnd == '\0')
    {
        // The entire string was numeric and converted successfully.
        return Value;
    }

    // Indicate a conversion error.
    return std::optional<size_t>();
}
