#ifndef _ASCIIUTILS_H
#define	_ASCIIUTILS_H

#include <string>

inline bool isWhitespace(char c)
{
    switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return true;
        default:
            return false;
    }
}

inline bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

inline bool isInteger(const std::string& string)
{
    if (string.empty())
        return false;
    int i = 0;
    if (string[0] == '-')
        ++i;
    if (i >= string.size())
        return false;
    while (i < string.size()) {
        if (!isDigit(string[i]))
            return false;
        ++i;
    }
    return true;
}

inline bool isLiteral(const std::string& string)
{
    if (string.size() < 2)
        return false;
    if (string[0] != '"' || string[string.size() - 1] != '"')
        return false;
    for (int i = 1; i < string.size() - 1; ++i) {
        if (string[i] == '"')
            return false;
    }
    return true;
}

#endif	/* _ASCIIUTILS_H */
