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
