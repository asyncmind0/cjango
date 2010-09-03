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
