
////
//// Created by Elliot Silveira on 9/14/21.
////
//
#include "StringAutomaton.h"
//
//
void StringAutomaton::S0(const std::string &input) {
    unsigned int i = inputRead;
    if (input[0] == '\'')
    {
        while (i < input.size())
        {
            i++;
            if (input[i] == '\'')
            {
                if (input[i + 1] == '\'')
                {
                    i+= 1;
                    continue;
                }
                i++;
                inputRead = i;
                return;
            }
            if (input[i] == '\n')
            {
                newLines++;
            }
        }
        inputRead = 0;
    }
}

