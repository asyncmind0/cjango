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
