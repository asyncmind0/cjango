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
