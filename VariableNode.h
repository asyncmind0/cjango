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
