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
