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

#include "Context.h"

Context::Context(const VariableMap& variables)
{
    m_variableStack.push_back(variables);
}

Context::~Context()
{
    m_variableStack.clear();
}

void Context::push()
{
    m_variableStack.push_back(VariableMap());
}

void Context::pop()
{
    assert(m_variableStack.size() > 1);

    m_variableStack.pop_back();
}

bool Context::contains(const std::string& key) const
{
    assert(!m_variableStack.empty());

    std::vector<VariableMap>::const_reverse_iterator it = m_variableStack.rbegin();
    std::vector<VariableMap>::const_reverse_iterator end = m_variableStack.rend();
    for (it; it != end; ++it) {
        const VariableMap& map = *it;
        if (map.find(key) != map.end())
            return true;
    }

    return false;
}

const Variant& Context::get(const std::string& key) const
{
    static Variant nullVariant;
    assert(!m_variableStack.empty());

    std::vector<VariableMap>::const_reverse_iterator it = m_variableStack.rbegin();
    std::vector<VariableMap>::const_reverse_iterator end = m_variableStack.rend();
    for (it; it != end; ++it) {
        const VariableMap& map = *it;
        VariableMap::const_iterator found = map.find(key);
        if (found != map.end())
            return found->second;
    }

    return nullVariant;
}

void Context::set(const std::string& key, const Variant& variant)
{
    assert(!m_variableStack.empty());

    VariableMap& map = m_variableStack.back();
    map[key] = variant;
}

void Context::remove(const std::string& key)
{
    assert(!m_variableStack.empty());

    VariableMap& map = m_variableStack.back();
    map.erase(key);
}
