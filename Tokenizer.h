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

#ifndef _TOKENIZER_H
#define	_TOKENIZER_H

#include "Defines.h"

#include <istream>
#include <string>

class Tokenizer {
public:
    class Token {
    public:
        enum Type {
            None,
            Text,
            OpenComment,
            CloseComment,
            OpenVariable,
            CloseVariable,
            OpenTag,
            CloseTag,
            EndOfInput
        };

        Token()
            : type(None)
        {
        }

        void clear()
        {
            type = None;
            contents.clear();
        }

        Type type;
        std::string contents;

    private:
        DISALLOW_COPY_AND_ASSIGN(Token)
    };

    enum State {
        None,
        Text,
        OpenComment,
        CommentText,
        CloseComment,
        OpenVariable,
        VariableExpression,
        LiteralInVariableExpression,
        CloseVariable,
        OpenTag,
        TagExpression,
        LiteralInTagExpression,
        CloseTag,
        EndOfInput
    };

    Tokenizer(std::istream* stream);
    ~Tokenizer();

    void nextToken(Token& token);

    const int& lineNumber() const { return m_lineNumber; }
    const int& columnNumber() const { return m_columnNumber; }

protected:
    inline bool nextCharacter(char& c);
    inline bool peekCharacter(char& c);

private:
    State m_state;
    std::istream* m_stream;

    int m_lineNumber;
    int m_columnNumber;
};

#endif	/* _TOKENIZER_H */
