//
// Created by Elliot Silveira on 9/26/21.
//

#include "Parser.h"



void Parser::ParseThisBaby(std::vector<Token*> &tokens)
{
    unsigned int i = 0;
    while (i < tokens.size())
    {
        if (tokens[i]->myType == TokenType::COMMENT) tokens.erase(tokens.begin() + i);
        else ++i;
    }
    // Check for SCHEMES and pop front
    Parser::Match(tokens, TokenType::SCHEMES);
    tokens.erase(tokens.begin());
    // Check for COLON and pop front
    Parser::Match(tokens, TokenType::COLON);
    tokens.erase(tokens.begin());
    // Parse Schemes
    Parser::ParseScheme(tokens);
    Parser::ParseSchemeList(tokens);

    // Check for FACTS and pop front
    Parser::Match(tokens, TokenType::FACTS);
    tokens.erase(tokens.begin());
    // Check for COLON and pop front
    Parser::Match(tokens, TokenType::COLON);
    tokens.erase(tokens.begin());
    // Parse Facts
    Parser::ParseFactList(tokens);

    // Check for RULES and pop front
    Parser::Match(tokens, TokenType::RULES);
    tokens.erase(tokens.begin());
    // Check for COLON and pop front
    Parser::Match(tokens, TokenType::COLON);
    tokens.erase(tokens.begin());
    // Parse Rules
    Parser::ParseRuleList(tokens);

    // Check for QUERIES and pop front
    Parser::Match(tokens, TokenType::QUERIES);
    tokens.erase(tokens.begin());
    // Check for COLON and pop front
    Parser::Match(tokens, TokenType::COLON);
    tokens.erase(tokens.begin());
    // Parse Rules
    Parser::ParseQuery(tokens);
    Parser::ParseQueryList(tokens);

    // Check for EOF
    Parser::Match(tokens, TokenType::EOF_TYPE);
    tokens.erase(tokens.begin());
}

void Parser::Match(std::vector <Token*> &tokens, TokenType rightType)
{
    std::string printType;
    switch (rightType) {
        case TokenType::ADD:
            printType = "ADD";
            break;
        case TokenType::MULTIPLY:
            printType = "MULTIPLY";
            break;
        case TokenType::COMMENT:
            printType = "COMMENT";
            break;
        case TokenType::UNDEFINED:
            printType = "UNDEFINED";
            break;
        case TokenType::COLON:
            printType = "COLON";
            break;
        case TokenType::COLON_DASH:
            printType = "COLON_DASH";
            break;
        case TokenType::COMMA:
            printType = "COMMA";
            break;
        case TokenType::PERIOD:
            printType = "PERIOD";
            break;
        case TokenType::QMARK:
            printType = "Q_MARK";
            break;
        case TokenType::LEFTPAREN:
            printType = "LEFT_PAREN";
            break;
        case TokenType::RIGHTPAREN:
            printType = "RIGHT_PAREN";
            break;
        case TokenType::QUERIES:
            printType = "QUERIES";
            break;
        case TokenType::FACTS:
            printType = "FACTS";
            break;
        case TokenType::SCHEMES:
            printType = "SCHEMES";
            break;
        case TokenType::EOF_TYPE:
            printType = "EOF";
            break;
        case TokenType::RULES:
            printType = "RULES";
            break;
        case TokenType::STRING:
            printType = "STRING";
            break;
        case TokenType::ID:
            printType = "ID";
            break;
    }
    if (tokens[0]->myType != rightType)
    {
//        std::stringstream error;
//        error << "Failure!\n  (" << tokens[0]->myDescription;
//        throw(error.str());
        Parser::Error(tokens);
    }
}

void Parser::ParseSchemeList(std::vector<Token *> &tokens)
{
    if (tokens[0]->myType == TokenType::ID)
    {
        Parser::ParseScheme(tokens);
        Parser::ParseSchemeList(tokens);
    }
}

void Parser::ParseFactList(std::vector<Token *> &tokens)
{
    if (tokens[0]->myType == TokenType::ID)
    {
        Parser::ParseFact(tokens);
        Parser::ParseFactList(tokens);
    }
}

void Parser::ParseRuleList(std::vector<Token *> &tokens)
{
    if (tokens[0]->myType == TokenType::ID)
    {
        Parser::ParseRule(tokens);
        Parser::ParseRuleList(tokens);
    }
}

void Parser::ParseQueryList(std::vector<Token *> &tokens)
{
    if (tokens[0]->myType == TokenType::ID)
    {
        Parser::ParseQuery(tokens);
        Parser::ParseQueryList(tokens);
    }
}

void Parser::ParseScheme(std::vector<Token *> &tokens)
{
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    // Create new scheme predicate
    Predicate* scheme = data->newScheme(tokens[0]->myDescription);
    tokens.erase(tokens.begin());
    // Check for LEFTPAREN and pop front
    Parser::Match(tokens, TokenType::LEFTPAREN);
    tokens.erase(tokens.begin());
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    // Add new parameter
    scheme->newParameter(tokens[0]->myDescription);
    tokens.erase(tokens.begin());
    // Call ID_List()
    Parser::ParseID_List(tokens, scheme);
//    Parser::ParseID_List(tokens);
    // Check RIGHTPAREN and pop front
    Parser::Match(tokens, TokenType::RIGHTPAREN);
    tokens.erase(tokens.begin());
}

void Parser::ParseFact(std::vector<Token *> &tokens)
{
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    Predicate* fact = data->newFact(tokens[0]->myDescription);
    tokens.erase(tokens.begin());
    // Check for LEFTPAREN and pop front
    Parser::Match(tokens, TokenType::LEFTPAREN);
    tokens.erase(tokens.begin());
    // Check for STRING and pop front
    Parser::Match(tokens, TokenType::STRING);
    fact->newParameter(tokens[0]->myDescription);
    tokens.erase(tokens.begin());

    Parser::ParseStringList(tokens, fact);

    // Check for RIGHTPAREN and pop front
    Parser::Match(tokens, TokenType::RIGHTPAREN);
    tokens.erase(tokens.begin());
    // Check for PERIOD and pop front
    Parser::Match(tokens, TokenType::PERIOD);
    tokens.erase(tokens.begin());
}

void Parser::ParseRule(std::vector<Token *> &tokens)
{
    Parser::ParseHeadPredicate(tokens);
    // Check COLON_DASH and pop front
    Parser::Match(tokens, TokenType::COLON_DASH);
    tokens.erase(tokens.begin());
    // Call ParsePredicate
    Predicate* body = head->newBody(tokens[0]->myDescription);
    Parser::ParsePredicate(tokens, body);
    // Call ParsePredicateList
    Parser::ParsePredicateList(tokens, body);

    // Check PERIOD and pop front
    Parser::Match(tokens, TokenType::PERIOD);
    tokens.erase(tokens.begin());
}

void Parser::ParseQuery(std::vector<Token *> &tokens)
{
    Predicate* query = data->newQuery(tokens[0]->myDescription);
    Parser::ParsePredicate(tokens, query);
    // Check for QMARK and pop front
    Parser::Match(tokens, TokenType::QMARK);
    tokens.erase(tokens.begin());
}

void Parser::ParseHeadPredicate(std::vector<Token *> &tokens)
{
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    head = data->newHead(tokens[0]->myDescription);
    tokens.erase(tokens.begin());
    // Check for LEFTPAREN and pop front
    Parser::Match(tokens, TokenType::LEFTPAREN);
    tokens.erase(tokens.begin());
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    head->newParameter(tokens[0]->myDescription);
    tokens.erase(tokens.begin());

    // Call ID_List()
    Parser::ParseID_List(tokens, head->getHead());
//    Parser::ParseID_List(tokens);
    // Check RIGHTPAREN and pop front
    Parser::Match(tokens, TokenType::RIGHTPAREN);
    tokens.erase(tokens.begin());
}

void Parser::ParsePredicate(std::vector<Token *> &tokens, Predicate* predicate)
{
    // Check for ID and pop front
    Parser::Match(tokens, TokenType::ID);
    tokens.erase(tokens.begin());
    // Check for LEFTPAREN and pop front
    Parser::Match(tokens, TokenType::LEFTPAREN);
    tokens.erase(tokens.begin());

    // Call ParseParameter
    Parser::ParseParameter(tokens, predicate);
    // Call ParseParameterList
    Parser::ParseParameterList(tokens, predicate);
    // Check RIGHTPAREN and pop front
    Parser::Match(tokens, TokenType::RIGHTPAREN);
    tokens.erase(tokens.begin());
}

void Parser::ParsePredicateList(std::vector<Token *> &tokens, Predicate* predicate)
{
    if (tokens[0]->myType == TokenType::COMMA)
    {
        // Check for COMMA and pop front
        Parser::Match(tokens, TokenType::COMMA);
        tokens.erase(tokens.begin());
        // Call ParsePredicate()
        predicate = head->newBody(tokens[0]->myDescription);
        Parser::ParsePredicate(tokens, predicate);
        // Recursively Call ParsePredicateList()
        Parser::ParsePredicateList(tokens, predicate);
    }
}

void Parser::ParseParameterList(std::vector<Token *> &tokens, Predicate* predicate)
{
    if (tokens[0]->myType == TokenType::COMMA)
    {
        // Check for COMMA and pop front
        Parser::Match(tokens, TokenType::COMMA);
        tokens.erase(tokens.begin());
        // Call ParseParameter()
        Parser::ParseParameter(tokens, predicate);
        // Recursively Call ParseParameterList()
        Parser::ParseParameterList(tokens, predicate);
    }
}

void Parser::ParseStringList(std::vector<Token *> &tokens, Predicate* predicate)
{
    if (tokens[0]->myType == TokenType::COMMA)
    {
        // Check for COMMA and pop front
        Parser::Match(tokens, TokenType::COMMA);
        tokens.erase(tokens.begin());
        // Check for STRING and pop front
        Parser::Match(tokens, TokenType::STRING);
        // Add new parameter
        predicate->newParameter(tokens[0]->myDescription);
        tokens.erase(tokens.begin());
        // Recursively Call StringList()
        Parser::ParseStringList(tokens, predicate);
    }
}

void Parser::ParseID_List(std::vector<Token *> &tokens, Predicate* predicate)
//void Parser::ParseID_List(std::vector<Token *> &tokens)
{
    if (tokens[0]->myType == TokenType::COMMA)
    {
        // Check for COMMA and pop front
        Parser::Match(tokens, TokenType::COMMA);
        tokens.erase(tokens.begin());
        // Check for ID and pop front
        Parser::Match(tokens, TokenType::ID);
        // Add new parameter
        predicate->newParameter(tokens[0]->myDescription);
        tokens.erase(tokens.begin());
        // Recursively Call ID_List()
//        Parser::ParseID_List(tokens);
        Parser::ParseID_List(tokens, predicate);
    }
}

void Parser::ParseParameter(std::vector<Token *> &tokens, Predicate* predicate)
{
    if (tokens[0]->myType == TokenType::STRING)
    {
        Parser::Match(tokens, TokenType::STRING);
        // Add new parameter
        predicate->newParameter(tokens[0]->myDescription);
        tokens.erase(tokens.begin());
    }
    else if (tokens[0]->myType == TokenType::ID)
    {
        Parser::Match(tokens, TokenType::ID);
        // Add new parameter
        predicate->newParameter(tokens[0]->myDescription);
        tokens.erase(tokens.begin());
    }
    else
    {
//        std::stringstream error;
//        error << "Failure!\n  (" << tokens[0]->myType << ;
//        throw(error);
        Parser::Match(tokens, TokenType::UNDEFINED);
    }
}

void Parser::Error(std::vector <Token*> &tokens)
{
    std::string printType;
    switch (tokens[0]->myType) {
        case TokenType::ADD:
            printType = "ADD";
            break;
        case TokenType::MULTIPLY:
            printType = "MULTIPLY";
            break;
        case TokenType::COMMENT:
            printType = "COMMENT";
            break;
        case TokenType::UNDEFINED:
            printType = "UNDEFINED";
            break;
        case TokenType::COLON:
            printType = "COLON";
            break;
        case TokenType::COLON_DASH:
            printType = "COLON_DASH";
            break;
        case TokenType::COMMA:
            printType = "COMMA";
            break;
        case TokenType::PERIOD:
            printType = "PERIOD";
            break;
        case TokenType::QMARK:
            printType = "Q_MARK";
            break;
        case TokenType::LEFTPAREN:
            printType = "LEFT_PAREN";
            break;
        case TokenType::RIGHTPAREN:
            printType = "RIGHT_PAREN";
            break;
        case TokenType::QUERIES:
            printType = "QUERIES";
            break;
        case TokenType::FACTS:
            printType = "FACTS";
            break;
        case TokenType::SCHEMES:
            printType = "SCHEMES";
            break;
        case TokenType::EOF_TYPE:
            printType = "EOF";
            break;
        case TokenType::RULES:
            printType = "RULES";
            break;
        case TokenType::STRING:
            printType = "STRING";
            break;
        case TokenType::ID:
            printType = "ID";
            break;
    }
    std::stringstream error;
    error << "Failure!\n  (" << printType << ",\"" << tokens[0]->myDescription << "\"," << tokens[0]->myLine << ")";
    throw(error.str());
}

void Parser::toString()
{
    std::cout << "Success!\n" << "Schemes(";
    data->print("schemes");
    std::cout << "Facts(";
    data->print("facts");
    std::cout << "Rules(";
    data->printRule();
    std::cout << "Queries(";
    data->print("queries");
    std::cout << "Domain(";
    data->printDomain();
    std::cout << std::endl << std::endl << std::endl;
}

