#include "TemplateNode.h"

#include "Context.h"

TemplateNode::TemplateNode()
    : Node(Template, 0)
{
}

TemplateNode::~TemplateNode()
{
}

void TemplateNode::render(Context* context, std::ostream* stream) const
{
    for (const Node* node = firstChild(); node; node = node->nextSibling())
        node->render(context, stream);
}
