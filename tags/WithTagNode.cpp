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

#include "WithTagNode.h"

#include "Context.h"
namespace cjango{

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
}

