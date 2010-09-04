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
