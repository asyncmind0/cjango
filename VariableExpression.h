#ifndef _VARIABLEEXPRESSION_H
#define	_VARIABLEEXPRESSION_H

#include "Context.h"
#include "Variant.h"

#include <string>
#include <vector>

class VariableExpression {
public:
    struct VariableFilterCall {
        std::string filterName;
        std::vector<Variant> arguments;
    };

public:
    static VariableExpression* parse(const std::string& expression);
    ~VariableExpression();

    const Variant& evaluate(Context* context) const;

    const std::string& name() const { return m_name; }
    const std::vector<VariableFilterCall>& filterCalls() const { return m_filterCalls; }

private:
    static Variant parseParameter(const std::string& expression);
    VariableExpression();

private:
    std::string m_name;
    std::vector<VariableFilterCall> m_filterCalls;
};

#endif	/* _VARIABLEEXPRESSION_H */
