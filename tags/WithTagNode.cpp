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

