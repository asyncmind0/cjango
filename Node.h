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
