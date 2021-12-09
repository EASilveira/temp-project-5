//
// Created by Elliot Silveira on 9/14/21.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input)
{
     //Line Comments
    unsigned int i = 0;
    if (input[0] == '#' && input[1] != '|')
    {
        while (input[i] != '\n' && i < input.size()) {
            ++i;
            ++inputRead;
        }
        return;
    }

    // Multiline Comments
    i = 2;
    if (input[0] == '#' && input[1] == '|')
    {
        inputRead += 2;
        while (i < input.size())
        {
            if (i == input.size() - 1) {
                inputRead = 0;
                return;
            }
            if (input[i] == '|' && input[i + 1] == '#')
            {
                i = input.size();
                inputRead += 2;
                continue;
            }
            if (input[i] == '\n') ++newLines;
            ++i;
            ++inputRead;
        }
        return;
    }


}
