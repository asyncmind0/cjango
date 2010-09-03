#include "TextNode.h"

#include "Context.h"

#include <cassert>

TextNode::TextNode(Node* parent)
    : Node(Text, parent)
{
}

TextNode::~TextNode()
{
}

void TextNode::render(Context* context, std::ostream* stream) const
{
    assert(!firstChild());
    *stream << m_text;
}
