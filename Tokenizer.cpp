#include "Tokenizer.h"

#include <cassert>
#include <istream>

Tokenizer::Tokenizer(std::istream* stream)
    : m_state(Text)
    , m_stream(stream)
    , m_lineNumber(0)
    , m_columnNumber(0)
{
}

Tokenizer::~Tokenizer()
{
}

#define WHICH_STATE(currentState) \
    switch (currentState)

#define BEGIN_STATE(state) \
    case state: \
    state:

#define END_STATE() \
    assert(0); \
    break;

#define CHANGE_STATE(state) \
    m_state = state; \
    return;

#define MOVE_TO_STATE(state) \
    if (!nextCharacter(c)) \
        return; \
    m_state = state; \
    goto state;

void Tokenizer::nextToken(Token& token)
{
    token.clear();

    char c, p;
    if (m_state != EndOfInput)
        nextCharacter(c);
    
    WHICH_STATE(m_state) {
        BEGIN_STATE(None) {
            assert(0);
        } END_STATE()

        BEGIN_STATE(Text) {
            token.type = Token::Text;

            if (c == '{') {
                if (!peekCharacter(p)) {
                    token.contents.push_back(c);
                    return;
                }

                switch (p) {
                    case '%':
                        if (token.contents.empty()) {
                            MOVE_TO_STATE(OpenTag);
                        } else {
                            CHANGE_STATE(OpenTag);
                        }
                        break;
                    case '{':
                        if (token.contents.empty()) {
                            MOVE_TO_STATE(OpenVariable);
                        } else {
                            CHANGE_STATE(OpenVariable);
                        }
                        break;
                    case '#':
                        if (token.contents.empty()) {
                            MOVE_TO_STATE(OpenComment);
                        } else {
                            CHANGE_STATE(OpenComment);
                        }
                        break;
                    default:
                        token.contents.push_back(c);
                        MOVE_TO_STATE(Text);
                        break;
                }
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(Text);
            }
        } END_STATE()

        BEGIN_STATE(OpenComment) {
            token.type = Token::OpenComment;
            CHANGE_STATE(CommentText);
        } END_STATE()

        BEGIN_STATE(CommentText) {
            token.type = Token::Text;

            if (c == '#') {
                if (!peekCharacter(p)) {
                    token.contents.push_back(c);
                    return;
                }

                if (p == '}') {
                    if (token.contents.empty()) {
                        MOVE_TO_STATE(CloseComment);
                    } else {
                        CHANGE_STATE(CloseComment);
                    }
                } else {
                    token.contents.push_back(c);
                    MOVE_TO_STATE(CommentText);
                }
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(CommentText);
            }
        } END_STATE()

        BEGIN_STATE(CloseComment) {
            token.type = Token::CloseComment;
            CHANGE_STATE(Text);
        } END_STATE()

        BEGIN_STATE(OpenVariable) {
            token.type = Token::OpenVariable;
            CHANGE_STATE(VariableExpression);
        } END_STATE()

        BEGIN_STATE(VariableExpression) {
            token.type = Token::Text;

            if (c == '}') {
                if (!peekCharacter(p)) {
                    token.contents.push_back(c);
                    return;
                }

                if (p == '}') {
                    if (token.contents.empty()) {
                        MOVE_TO_STATE(CloseVariable);
                    } else {
                        CHANGE_STATE(CloseVariable);
                    }
                } else {
                    token.contents.push_back(c);
                    MOVE_TO_STATE(VariableExpression);
                }
            } else if (c == '"') {
                token.contents.push_back(c);
                MOVE_TO_STATE(LiteralInVariableExpression);
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(VariableExpression);
            }
        } END_STATE()

        BEGIN_STATE(LiteralInVariableExpression) {
            token.type = Token::Text;

            if (c == '"') {
                token.contents.push_back(c);
                MOVE_TO_STATE(VariableExpression);
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(LiteralInVariableExpression);
            }
        } END_STATE()

        BEGIN_STATE(CloseVariable) {
            token.type = Token::CloseVariable;
            CHANGE_STATE(Text);
        } END_STATE()

        BEGIN_STATE(OpenTag) {
            token.type = Token::OpenTag;
            CHANGE_STATE(TagExpression);
        } END_STATE()

        BEGIN_STATE(TagExpression) {
            token.type = Token::Text;

            if (c == '%') {
                if (!peekCharacter(p)) {
                    token.contents.push_back(c);
                    return;
                }

                if (p == '}') {
                    if (token.contents.empty()) {
                        MOVE_TO_STATE(CloseTag);
                    } else {
                        CHANGE_STATE(CloseTag);
                    }
                } else {
                    token.contents.push_back(c);
                    MOVE_TO_STATE(TagExpression);
                }
            } else if (c == '"') {
                token.contents.push_back(c);
                MOVE_TO_STATE(LiteralInTagExpression);
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(TagExpression);
            }
        } END_STATE()

        BEGIN_STATE(LiteralInTagExpression) {
            token.type = Token::Text;

            if (c == '"') {
                token.contents.push_back(c);
                MOVE_TO_STATE(TagExpression);
            } else {
                token.contents.push_back(c);
                MOVE_TO_STATE(LiteralInTagExpression);
            }
        } END_STATE()

        BEGIN_STATE(CloseTag) {
            token.type = Token::CloseTag;
            CHANGE_STATE(Text);
        } END_STATE()

        BEGIN_STATE(EndOfInput) {
            token.type = Token::EndOfInput;
            CHANGE_STATE(None);
        } END_STATE()
    }
}

bool Tokenizer::nextCharacter(char& c)
{
    assert(m_state != EndOfInput);
    c = m_stream->get();
    if (!m_stream->good()) {
        m_state = EndOfInput;
        return false;
    }

    if (c == '\n') {
        ++m_lineNumber;
        m_columnNumber = 0;
    } else {
        ++m_columnNumber;
    }
    return true;
}

bool Tokenizer::peekCharacter(char& c)
{
    assert(m_state != EndOfInput);
    c = m_stream->peek();
    if (!m_stream->good()) {
        m_state = EndOfInput;
        return false;
    }
    return true;
}
