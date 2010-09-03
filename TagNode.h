#ifndef _TAGNODE_H
#define	_TAGNODE_H

#include "Node.h"

#include <string>
#include <vector>

class TagNode : public Node {
public:
    TagNode(Node* parent);
    ~TagNode();

    const std::string& name() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

    const std::vector<std::string>& parameters() const { return m_parameters; }
    void setParameters(const std::vector<std::string>& parameters) { m_parameters = parameters; }

    virtual bool isSelfClosing() const = 0;

private:
    std::string m_name;
    std::vector<std::string> m_parameters;
};

#endif	/* _TAGNODE_H */
