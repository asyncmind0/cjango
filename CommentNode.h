#ifndef _COMMENTNODE_H
#define	_COMMENTNODE_H

#include "Node.h"

#include <ostream>
#include <string>

class Context;
class CommentNode : public Node {
public:
    CommentNode(Node* parent);
    ~CommentNode();

    const std::string& text() const { return m_text; }
    void setText(const std::string& text) { m_text = text; }

    void render(Context* context, std::ostream* stream) const;
    
private:
    std::string m_text;
};

#endif	/* _COMMENTNODE_H */
