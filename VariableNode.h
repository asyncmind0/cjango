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

#ifndef _VARIABLENODE_H
#define	_VARIABLENODE_H

#include "Node.h"

#include "VariableExpression.h"

#include <cassert>
#include <ostream>
#include <string>

class VariableNode : public Node {
public:
    VariableNode(Node* parent);
    ~VariableNode();

    const VariableExpression* expression() const { return m_expression; }
    void setExpression(const VariableExpression* expression) { assert(!m_expression); m_expression = expression; }
    
    void render(Context* context, std::ostream* stream) const;

private:
    const VariableExpression* m_expression;
};

#endif	/* _VARIABLENODE_H */
