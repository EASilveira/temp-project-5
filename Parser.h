//
// Created by Elliot Silveira on 9/26/21.
//

#ifndef PROJECT_2_PARSER_H
#define PROJECT_2_PARSER_H

#include "Lexer.h"
#include "sstream"
#include "Predicate.h"
#include "Rule.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include <sstream>


class Parser {
private:
    void ParseSchemeList(std::vector<Token*> &tokens);
    void ParseFactList(std::vector<Token*> &tokens);
    void ParseRuleList(std::vector<Token*> &tokens);
    void ParseQueryList(std::vector<Token*> &tokens);

    void ParseScheme(std::vector<Token*> &tokens);
    void ParseFact(std::vector<Token*> &tokens);
    void ParseRule(std::vector<Token*> &tokens);
    void ParseQuery(std::vector<Token*> &tokens);

    void ParseHeadPredicate(std::vector<Token*> &tokens);
    void ParsePredicate(std::vector<Token*> &tokens, Predicate* predicate);

    void ParsePredicateList(std::vector<Token*> &tokens, Predicate* predicate);
    void ParseParameterList(std::vector<Token*> &tokens, Predicate* predicate);
    void ParseStringList(std::vector<Token*> &tokens, Predicate*);
    void ParseID_List(std::vector<Token*> &tokens, Predicate*);
    void ParseParameter(std::vector<Token*> &tokens, Predicate* predicate);
    void Match(std::vector<Token*> &tokens, TokenType);
    void Error(std::vector <Token*> &tokens);

public:
    DatalogProgram* data = new class DatalogProgram();
    Rule* head;
    Parser() {};
    ~Parser() {};

    void ParseThisBaby(std::vector<Token*> &tokens);
    void toString();
    DatalogProgram* getData() {return data;}
};


#endif //PROJECT_2_PARSER_H
