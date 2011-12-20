/**
 * Copyright (C) 2010 Jakub Wieczorek <fawek@fawek.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
