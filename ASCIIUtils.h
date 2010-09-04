/**
 * Copyright (C) 2010  Jakub Wieczorek <fawek@fawek.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
