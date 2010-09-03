#ifndef _TEMPLATENODE_H
#define	_TEMPLATENODE_H

#include "Node.h"

#include <ostream>

class Context;
class TemplateNode : public Node {
public:
    TemplateNode();
    ~TemplateNode();

    void render(Context* context, std::ostream* stream) const;
};

#endif	/* _TEMPLATENODE_H */
