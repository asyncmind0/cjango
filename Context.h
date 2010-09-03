#ifndef _CONTEXT_H
#define	_CONTEXT_H

#include "Variant.h"

#include <string>
#include <tr1/unordered_map>
#include <vector>

typedef std::tr1::unordered_map<std::string, Variant> VariableMap;

class Context {
public:
    Context(const VariableMap& variables = VariableMap());
    ~Context();

    void push();
    void pop();

    bool contains(const std::string& key) const;
    const Variant& get(const std::string& key) const;
    void set(const std::string& key, const Variant& variant);
    void remove(const std::string& key);

private:
    std::vector<VariableMap> m_variableStack;
};

#endif	/* _CONTEXT_H */
