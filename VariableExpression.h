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
