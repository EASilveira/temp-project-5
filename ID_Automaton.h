//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_ID_AUTOMATON_H
#define PROJECT1_STARTER_CODE_ID_AUTOMATON_H

#include "Automaton.h"

class ID_Automaton : public Automaton
{
public:
    ID_Automaton() : Automaton(TokenType::ID) {}

    void S0(const std::string &input);
};


#endif //PROJECT1_STARTER_CODE_ID_AUTOMATON_H
