//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H
#define PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFTPAREN) {}

    void S0(const std::string &input);
};


#endif //PROJECT1_STARTER_CODE_LEFTPARENAUTOMATON_H
