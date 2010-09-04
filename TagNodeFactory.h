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

#ifndef _TAGNODEFACTORY_H
#define	_TAGNODEFACTORY_H

#include "HashUtils.h"
#include "TagNode.h"

#include <cstring>
#include <tr1/unordered_map>

struct stringCompare {
    inline bool operator()(const char *s1, const char *s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};

typedef TagNode* (*TagNodeFactoryFunction)(Node* parent);
typedef std::tr1::unordered_map<const char*, TagNodeFactoryFunction, stringHash, stringCompare> TagNodeFactoryMap;

class TagNodeFactory {
public:
    static TagNodeFactory* self();

    TagNode* create(const char* tagName, Node* parent) const;
    void registerTag(const char* tagName, TagNodeFactoryFunction function);
    bool isTagRegistered(const char* tagName);

private:
    TagNodeFactory();
    ~TagNodeFactory();

private:
    TagNodeFactoryMap m_factoryMap;
};

#endif	/* _TAGNODEFACTORY_H */
