#ifndef _TAGNODEFACTORY_H
#define	_TAGNODEFACTORY_H

#include "TagNode.h"

#include <tr1/unordered_map>

typedef TagNode* (*TagNodeFactoryFunction)(Node* parent);
typedef std::tr1::unordered_map<const char*, TagNodeFactoryFunction> TagNodeFactoryMap;

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
