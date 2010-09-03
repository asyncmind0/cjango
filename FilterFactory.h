#ifndef _FILTERFACTORY_H
#define	_FILTERFACTORY_H

#include "Filter.h"
#include "Variant.h"

#include <tr1/unordered_map>

typedef std::tr1::unordered_map<const char*, Filter*> FilterMap;

class FilterFactory {
public:
    static FilterFactory* self();

    Filter* get(const char* filterName) const;
    void registerFilter(const char* filterName, Filter* filter);
    bool isFilterRegistered(const char* filterName);

private:
    FilterFactory();
    ~FilterFactory();

private:
    FilterMap m_factoryMap;
};

#endif	/* _FILTERFACTORY_H */
