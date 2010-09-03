#ifndef _FILTER_H
#define	_FILTER_H

#include "Variant.h"

#include <vector>

class Filter {
public:
    Filter();
    ~Filter();

    virtual bool apply(Variant& variant, const std::vector<Variant>& arguments) const = 0;
};

#endif	/* _FILTER_H */
