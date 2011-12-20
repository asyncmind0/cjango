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
