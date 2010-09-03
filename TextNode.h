#ifndef _TEXTNODE_H
#define	_TEXTNODE_H

#include "Node.h"

#include <ostream>
#include <string>

class Context;
class TextNode : public Node {
public:
    TextNode(Node* parent);
    ~TextNode();

    const std::string& text() const { return m_text; }
    void setText(const std::string& text) { m_text = text; }

    void render(Context* context, std::ostream* stream) const;

private:
    std::string m_text;
};

#endif	/* _TEXTNODE_H */
