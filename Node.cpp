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

#include "Node.h"

#include <cassert>

Node::Node(Type type, Node* parent)
    : m_type(type)
    , m_parent(0)
    , m_firstChild(0)
    , m_lastChild(0)
    , m_nextSibling(0)
    , m_previousSibling(0)
{
    if (parent)
        parent->append(this);
}

Node::~Node()
{
}

void Node::append(Node* node)
{
    assert(!node->parent());
    assert(!node->previousSibling());
    assert(!node->nextSibling());
    node->setParent(this);

    if (!firstChild()) {
        assert(!lastChild());
        setFirstChild(node);
        setLastChild(node);
    } else {
        assert(lastChild());
        Node* lastChild = this->lastChild();
        assert(!lastChild->nextSibling());
        lastChild->setNextSibling(node);
        node->setPreviousSibling(lastChild);
        setLastChild(node);
    }
}
