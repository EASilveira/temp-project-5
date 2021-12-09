//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_QMARKAUTOMATON_H
#define PROJECT1_STARTER_CODE_QMARKAUTOMATON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton
{
public:
    QMarkAutomaton() : Automaton(TokenType::QMARK) {}

    void S0(const std::string &input);
};


#endif //PROJECT1_STARTER_CODE_QMARKAUTOMATON_H
