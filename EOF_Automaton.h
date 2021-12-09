//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_EOF_AUTOMATON_H
#define PROJECT1_STARTER_CODE_EOF_AUTOMATON_H

#include "Automaton.h"
class EOF_Automaton : public Automaton
{
public:
    EOF_Automaton() : Automaton(TokenType::EOF_TYPE) {}
    void S0(const std::string &input) {}
};


#endif //PROJECT1_STARTER_CODE_EOF_AUTOMATON_H
