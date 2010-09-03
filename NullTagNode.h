#ifndef _NULLTAGNODE_H
#define	_NULLTAGNODE_H

#include "TagNode.h"

class NullTagNode : public TagNode {
public:
    NullTagNode(Node* parent);
    ~NullTagNode();

    void render(Context* context, std::ostream* stream) const;

    bool isSelfClosing() const { return true; }
};

#endif	/* _NULLTAGNODE_H */
