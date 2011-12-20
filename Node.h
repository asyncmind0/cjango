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
