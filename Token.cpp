#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    myType = type;
    myDescription = description;
    myLine = line;
}
