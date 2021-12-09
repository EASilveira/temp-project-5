#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    PERIOD,
    QMARK,
    LEFTPAREN,
    RIGHTPAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE,
};

class Token
{
private:
    // TODO: add member variables for information needed by Token

public:
    std::string myDescription;
    TokenType myType;
    int myLine;
    Token(TokenType type, std::string description, int line);
    // TODO: add other needed methods
};

#endif // TOKEN_H

