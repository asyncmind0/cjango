#ifndef _WITHTAGNODE_H
#define _WITHTAGNODE_H

#include "TagNode.h"

#include "Node.h"

class WithTagNode : public TagNode {
public:
    WithTagNode(Node* parent);
    ~WithTagNode();
    
    bool isSelfClosing() const { return false; }
    
    void render(Context* context, std::ostream* stream) const;
};

#endif  /* _WITHTAGNODE_H */

