/**
 * Copyright (C) 2010 Jakub Wieczorek <fawek@fawek.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
