#include "NullTagNode.h"

NullTagNode::NullTagNode(Node* parent)
    : TagNode(parent)
{
}

NullTagNode::~NullTagNode()
{
}

void NullTagNode::render(Context* context, std::ostream* stream) const
{
    // Do nothing.
}
