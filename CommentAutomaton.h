//
// Created by Elliot Silveira on 9/14/21.
//

#ifndef PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H

#include "Automaton.h"
class CommentAutomaton :public Automaton
{
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}
    void S0(const std::string &input);
};


#endif //PROJECT1_STARTER_CODE_COMMENTAUTOMATON_H
