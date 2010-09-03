#include "CommentNode.h"

#include "Context.h"

#include <cassert>

CommentNode::CommentNode(Node* parent)
    : Node(Comment, parent)
{
}

CommentNode::~CommentNode()
{
}

void CommentNode::render(Context* context, std::ostream* stream) const
{
    assert(!firstChild());
    // Do nothing, comment nodes do not render into the output stream.
}
