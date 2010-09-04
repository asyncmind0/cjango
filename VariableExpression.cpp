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
