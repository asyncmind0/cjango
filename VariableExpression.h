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

#ifndef _CJANGO_VARIABLEEXPRESSION_H
#define	_CJANGO_VARIABLEEXPRESSION_H

#include "Context.h"
#include "Variant.h"

#include <string>
#include <vector>

namespace cjango{
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
}
#endif	/* _VARIABLEEXPRESSION_H */
