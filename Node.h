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

#ifndef _NODE_H
#define	_NODE_H

#include <ostream>

class Context;
class Node {
public:
    enum Type {
        Template,
        Text,
        Tag,
        Variable,
        Comment
    };

    virtual ~Node();

    const Type& type() const { return m_type; }

    const Node* parent() const { return m_parent; }
    Node* parent() { return m_parent; }

    const Node* firstChild() const { return m_firstChild; }
    Node* firstChild() { return m_firstChild; }

    const Node* lastChild() const { return m_lastChild; }
    Node* lastChild() { return m_lastChild; }

    const Node* nextSibling() const { return m_nextSibling; }
    Node* nextSibling() { return m_nextSibling; }

    const Node* previousSibling() const { return m_previousSibling; }
    Node* previousSibling() { return m_previousSibling; }

    void append(Node* node);

    virtual void render(Context* context, std::ostream* stream) const = 0;

protected:
    Node(Type type, Node* parent);

    void setParent(Node* node) { m_parent = node; }
    void setFirstChild(Node* node) { m_firstChild = node; }
    void setLastChild(Node* node) { m_lastChild = node; }
    void setNextSibling(Node* node) { m_nextSibling = node; }
    void setPreviousSibling(Node* node) { m_previousSibling = node; }

private:
    const Type m_type;

    Node* m_parent;
    Node* m_firstChild;
    Node* m_lastChild;
    Node* m_nextSibling;
    Node* m_previousSibling;
};

#endif	/* _NODE_H */
