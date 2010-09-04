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
