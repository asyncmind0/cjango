#include "VariableExpression.h"

#include "ASCIIUtils.h"
#include "FilterFactory.h"
#include "VariantUtils.h"

#include <cstdlib>

// The cleanest way would be to have a separate tokenizer for variable expressions.
VariableExpression* VariableExpression::parse(const std::string& expression)
{
    VariableExpression* expr = new VariableExpression();

    int i = 0;
    while (i < expression.size() && expression[i] != '|')
        ++i;
    expr->m_name = expression.substr(0, i);

    while (i < expression.size() && expression[i] == '|') {
        ++i;
        int j = i;

        expr->m_filterCalls.push_back(VariableFilterCall());
        VariableFilterCall& call = expr->m_filterCalls.back();

        while (j < expression.size() && expression[j] != '|' && expression[j] != ':')
            ++j;
        call.filterName = expression.substr(i, j);

        while (i < expression.size() && expression[i] == ':') {
            ++i;
            j = i;

            bool inLiteral = false;
            while (j < expression.size() && expression[j] != '|' && (inLiteral || expression[j] != ':')) {
                if (expression[j] == '"')
                    inLiteral = !inLiteral;
                ++j;
            }

            std::string parameter = expression.substr(i, j - i);
            call.arguments.push_back(variantFromString(parameter));
        }
    }

    return expr;
}

VariableExpression::VariableExpression()
{
}

VariableExpression::~VariableExpression()
{
}

const Variant& VariableExpression::evaluate(Context* context) const
{
    FilterFactory* filterFactory = FilterFactory::self();

    Variant value = context->get(m_name);
    std::vector<VariableFilterCall>::const_iterator it = m_filterCalls.begin();
    std::vector<VariableFilterCall>::const_iterator end = m_filterCalls.end();
    for (it; it != end; ++it) {
        const VariableFilterCall& call = *it;
        if (Filter* filter = filterFactory->get(call.filterName.c_str()))
            filter->apply(value, call.arguments);
    }

    return context->get(m_name);
}
