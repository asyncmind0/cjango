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
