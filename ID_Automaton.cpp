//
// Created by Elliot Silveira on 9/14/21.
//

#include "ID_Automaton.h"

void ID_Automaton::S0(const std::string &input) {
    if (isalpha(input[0]))
    {
        while(input[inputRead] != ' ' && (isalpha(input[inputRead]) || isdigit(input[inputRead]))) ++inputRead;
    }
}