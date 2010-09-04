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

#include "TagNodeFactory.h"

#include "Node.h"

#include <cassert>

#include "WithTagNode.h"

template <typename TagNodeClass>
static TagNode* createTagNode(Node* parent)
{
    return new TagNodeClass(parent);
}

void registerBuiltinTags(TagNodeFactory* factory)
{
    factory->registerTag("with", createTagNode<WithTagNode>);
}

TagNodeFactory* TagNodeFactory::self()
{
    static TagNodeFactory* factory = 0;
    if (!factory) {
        factory = new TagNodeFactory();
        registerBuiltinTags(factory);
    }
    return factory;
}

TagNodeFactory::TagNodeFactory()
{
}

TagNodeFactory::~TagNodeFactory()
{
}

TagNode* TagNodeFactory::create(const char* tagName, Node* parent) const
{
    TagNodeFactoryMap::const_iterator it = m_factoryMap.find(tagName);
    if (it == m_factoryMap.end())
        return 0;

    TagNodeFactoryFunction function = it->second;
    return function(parent);
}

void TagNodeFactory::registerTag(const char* tagName, TagNodeFactoryFunction function)
{
    assert(m_factoryMap.find(tagName) == m_factoryMap.end());
    m_factoryMap[tagName] = function;
}

bool TagNodeFactory::isTagRegistered(const char* tagName)
{
    return m_factoryMap.find(tagName) != m_factoryMap.end();
}
