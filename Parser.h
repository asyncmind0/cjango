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

#ifndef _PARSER_H
#define	_PARSER_H

#include "Tokenizer.h"

#include <istream>

class TemplateNode;
class Parser {
public:
    Parser(std::istream* stream);
    ~Parser();

    TemplateNode* parse();
    
private:
    bool m_insideClause;
    Tokenizer::Token::Type m_lastTokenType;
    Tokenizer* m_tokenizer;
};

#endif	/* _PARSER_H */
