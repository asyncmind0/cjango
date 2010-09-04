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
