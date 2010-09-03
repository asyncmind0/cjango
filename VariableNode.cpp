#include "VariableNode.h"

#include "Variant.h"
#include "VariantUtils.h"

#include <string>

VariableNode::VariableNode(Node* parent)
    : Node(Variable, parent)
    , m_expression(0)
{
}

VariableNode::~VariableNode()
{
}

void VariableNode::render(Context* context, std::ostream* stream) const
{
    assert(m_expression);
    Variant value = m_expression->evaluate(context);
    *stream << value;
}
