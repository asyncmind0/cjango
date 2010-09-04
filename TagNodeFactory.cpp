#include "TagNodeFactory.h"

#include "Node.h"

#include <cassert>

#include "WithTagNode.h"

template <typename TagNodeClass>
static TagNode* createTagNode(Node* parent)
{
    return new TagNodeClass(parent);
}

void registerBuiltinTags()
{
    TagNodeFactory* factory = TagNodeFactory::self();
    factory->registerTag("with", createTagNode<WithTagNode>);
}

TagNodeFactory* TagNodeFactory::self()
{
    static TagNodeFactory* factory = 0;
    if (!factory) {
        factory = new TagNodeFactory();
        registerBuiltinTags();
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
