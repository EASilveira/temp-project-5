//
// Created by Elliot Silveira on 9/28/21.
//

#include "Rule.h"

void Rule::toString()
{
    // Print Head
    std::cout << "  " << headPredicate->id << "(";
    for (unsigned int i = 0; i < headPredicate->parameters.size(); ++i)
    {
        if (i == 0) std::cout << headPredicate->parameters[i]->p;
        else std::cout << "," << headPredicate->parameters[i]->p;
    }
    std::cout << ") :- ";

    // Print Body Predicates
    for (unsigned int i = 0; i < bodyPredicates.size(); ++i)
    {
        std::cout << bodyPredicates[i]->id << "(";
        for (unsigned int j = 0; j < bodyPredicates[i]->parameters.size(); ++j)
        {
            if (j == 0) std::cout << bodyPredicates[i]->parameters[j]->p;
            else std::cout << "," << bodyPredicates[i]->parameters[j]->p;
        }
        if (i + 1 < bodyPredicates.size()) std::cout << "),";
    }
    std::cout << ").\n";
}