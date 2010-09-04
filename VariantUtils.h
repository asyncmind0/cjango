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

#ifndef _VARIANTUTILS_H
#define	_VARIANTUTILS_H

#include "ASCIIUtils.h"
#include "Variant.h"

#include <cstdlib>
#include <string>

// The c_str() calls are unacceptable. We really should only be operating on an char*
// in such a critical part.
inline Variant variantFromString(const std::string& string)
{
    if (isLiteral(string))
        return Variant(string.substr(1, string.size() - 2));
    else if (isInteger(string))
        return Variant(static_cast<int>(strtol(string.c_str(), 0, 10)));
    else
        return Variant(); // FIXME: how about real numbers?
}

// Maybe this should be generically supported in Variant itself?
// An operator<< overload that would work as long as the underlying type
// has that overload.
// That way, I wouldn't need to restrict the subset of supported types to the
// ones listed below, which may be not enough.
inline std::ostream& operator<<(std::ostream& stream, const Variant& variant)
{
    if (!variant.isNull()) {
        if (variant.type() == typeid(int)) {
            stream << variant.get<int>();
        } else if (variant.type() == typeid(double)) {
            stream << variant.get<double>();
        } else if (variant.type() == typeid(std::string)) {
            stream << variant.get<std::string>();
        } else {
            // Anything else?
        }
    }

    return stream;
}

#endif	/* _VARIANTUTILS_H */
