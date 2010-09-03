#include "Parser.h"

#include "ASCIIUtils.h"
#include "CommentNode.h"
#include "Node.h"
#include "NullTagNode.h"
#include "TagNode.h"
#include "TagNodeFactory.h"
#include "TemplateNode.h"
#include "TextNode.h"
#include "Tokenizer.h"
#include "TagNodeFactory.h"
#include "VariableNode.h"

#include <cassert>

Parser::Parser(std::istream* stream)
    : m_tokenizer(new Tokenizer(stream))
    , m_lastTokenType(Tokenizer::Token::None)
    , m_insideClause(false)
{
}

Parser::~Parser()
{
    delete m_tokenizer;
}

// This could go even further and tokenize the parameters into a list although
// that does not leave as much flexibility for the tag nodes as it should.
// For instance, what would we do with literals? Should we allow spaces to appear
// in them without being split? But then, a tag might want to treat a single " as
// a normal character, which it could not because we'd treat as a parse error.
bool splitTagExpression(const std::string& expression, std::string& tagName, std::vector<std::string>& parameters)
{
    int i = 0;
    int j = expression.size() - 1;
    while (i < j && isWhitespace(expression[i]))
        ++i;
    while (j > i && isWhitespace(expression[j]))
        --j;
    if (i == j)
        return false;

    int k = i;
    while (k <= j && !isWhitespace(expression[k]))
        ++k;

    tagName = expression.substr(i, k - i);

    assert(parameters.empty());
    while (k < j && isWhitespace(expression[k]))
        ++k;

    if (k != j) {
        while (k < j && isWhitespace(expression[k]))
            ++k;

        bool inLiteral = false;
        while (k < j) {
            while (k < j && isWhitespace(expression[k]))
                ++k;
            i = k;
            while (k < j && (inLiteral || !isWhitespace(expression[k]))) {
                if (expression[k] == '"')
                    inLiteral = !inLiteral;
                ++k;
            }

            parameters.push_back(std::string());
            parameters.back() = expression.substr(i, k - i);
        }
    }
    
    return true;
}

// For now, this just removes trailing whitespaces.
// I'm still unsure where the variable parsing should take place.
bool splitVariableExpression(const std::string& expression, std::string& variable)
{
    int i = 0;
    int j = expression.size() - 1;
    while (i < j && isWhitespace(expression[i]))
        ++i;
    while (j > i && isWhitespace(expression[j]))
        --j;
    if (i == j)
        return false;

    variable = expression.substr(i, j - i + 1);

    return true;
}

// FIXME: Most of the assertions below should be turn into parse errors and be
// reported in a cleaner way to the client side.
TemplateNode* Parser::parse()
{
    TemplateNode* root = new TemplateNode();
    Node* current = root;

    m_insideClause = false;

    Tokenizer::Token token;
    do {
        assert(m_lastTokenType != Tokenizer::Token::EndOfInput);
        m_tokenizer->nextToken(token);
        assert(token.type != Tokenizer::Token::None);

        switch (token.type) {
            case Tokenizer::Token::Text:
                assert(m_lastTokenType != Tokenizer::Token::Text);
                switch (m_lastTokenType) {
                    case Tokenizer::Token::OpenComment: {
                        assert(m_insideClause);
                        
                        CommentNode* commentNode = new CommentNode(current);
                        commentNode->setText(token.contents);
                        break;
                    }
                    case Tokenizer::Token::OpenVariable: {
                        assert(m_insideClause);
                        std::string variable;
                        assert(splitVariableExpression(token.contents, variable));

                        VariableNode* variableNode = new VariableNode(current);
                        variableNode->setExpression(VariableExpression::parse(variable));
                        break;
                    }
                    case Tokenizer::Token::OpenTag: {
                        assert(m_insideClause);
                        std::string tagName;
                        std::vector<std::string> parameters;
                        assert(splitTagExpression(token.contents, tagName, parameters));
                        
                        if (tagName.size() > 3 && tagName.substr(0, 3) == "end") {
                            std::string tagBaseName = tagName.substr(3);
                            if (TagNodeFactory::self()->isTagRegistered(tagBaseName.c_str())) {
                                assert(current->type() == Node::Tag);
                                TagNode* tagNode = static_cast<TagNode*>(current);
                                assert(tagNode->name() == tagBaseName);
                                assert(!tagNode->isSelfClosing());
                                current = current->parent();
                            } else {
                                TagNode* tagNode = new NullTagNode(current);
                                assert(tagNode->isSelfClosing());
                            }
                        } else {
                            if (TagNodeFactory::self()->isTagRegistered(tagName.c_str())) {
                                TagNode* tagNode = TagNodeFactory::self()->create(tagName.c_str(), current);
                                assert(tagNode);
                                tagNode->setName(tagName);
                                tagNode->setParameters(parameters);
                                if (!tagNode->isSelfClosing())
                                    current = tagNode;
                            } else {
                                TagNode* tagNode = new NullTagNode(current);
                                assert(tagNode->isSelfClosing());
                            }
                        }

                        break;
                    }
                    default: {
                        TextNode* textNode = new TextNode(current);
                        textNode->setText(token.contents);
                        break;
                    }
                }
                break;
            case Tokenizer::Token::OpenComment:
            case Tokenizer::Token::OpenVariable:
            case Tokenizer::Token::OpenTag:
                assert(!m_insideClause);
                m_insideClause = true;
                break;
            case Tokenizer::Token::CloseComment:
            case Tokenizer::Token::CloseVariable:
            case Tokenizer::Token::CloseTag:
                assert(m_insideClause);
                m_insideClause = false;
                break;
            case Tokenizer::Token::EndOfInput:
                // Make sure all opening tags have their corresponding closing tags.
                assert(current == root);
                break;
        }

        m_lastTokenType = token.type;
        assert(current);
    } while (token.type != Tokenizer::Token::EndOfInput);

    return root;
}
