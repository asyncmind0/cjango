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
