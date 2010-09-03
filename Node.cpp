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
