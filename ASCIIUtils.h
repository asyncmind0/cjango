/**
 * Copyright (C) 2010 Jakub Wieczorek <fawek@fawek.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _CJANGO_ASCIIUTILS_H
#define	_CJANGO_ASCIIUTILS_H

#include <string>
namespace cjango{
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

}
#endif	/* _ASCIIUTILS_H */
