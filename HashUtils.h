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

#ifndef _HASHUTILS_H
#define _HASHUTILS_H

#include <tr1/functional>

struct stringHash : public std::unary_function<const char*, size_t>
{
    size_t operator()(const char* str) const
    { 
        size_t hash = 0;
        while (*str != '\0')
            hash += hash * 42 + *str++;
        return hash;
    }
};

#endif  /* _HASHUTILS_H */

