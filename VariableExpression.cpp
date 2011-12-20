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
