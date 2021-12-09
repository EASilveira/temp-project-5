//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMAAUTOMATON_H

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}

    void S0(const std::string &input);
};


#endif //PROJECT1_STARTER_CODE_COMMAAUTOMATON_H
