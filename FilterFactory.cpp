#include "FilterFactory.h"

#include <cassert>

FilterFactory* FilterFactory::self()
{
    static FilterFactory* factory = 0;
    if (!factory)
        factory = new FilterFactory();
    return factory;
}

FilterFactory::FilterFactory()
{
}

FilterFactory::~FilterFactory()
{
}

Filter* FilterFactory::get(const char* filterName) const
{
    FilterMap::const_iterator it = m_factoryMap.find(filterName);
    if (it == m_factoryMap.end())
        return 0;
    return it->second;
}

void FilterFactory::registerFilter(const char* filterName, Filter* filter)
{
    assert(m_factoryMap.find(filterName) == m_factoryMap.end());
    m_factoryMap[filterName] = filter;
}

bool FilterFactory::isFilterRegistered(const char* filterName)
{
    return m_factoryMap.find(filterName) != m_factoryMap.end();
}
