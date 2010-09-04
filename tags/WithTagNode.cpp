#include "WithTagNode.h"

#include "Context.h"

WithTagNode::WithTagNode(Node* parent)
    : TagNode(parent)
{
}

WithTagNode::~WithTagNode()
{
}

void WithTagNode::render(Context* context, std::ostream* stream) const
{
    const std::vector<std::string>& parameters = this->parameters();
    assert(parameters.size() == 3);

    const std::string& variable = parameters[0];
    assert(parameters[1] == "as");
    const std::string& alias = parameters[2];

    context->push();
    context->set(alias, context->get(variable));
    
    for (const Node* node = firstChild(); node; node = node->nextSibling())
        node->render(context, stream);
    
    context->pop();
}

