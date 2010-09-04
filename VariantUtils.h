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
