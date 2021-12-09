//
// Created by Elliot Silveira on 9/27/21.
//

#include "DatalogProgram.h"
#include <set>

void DatalogProgram::toString(std::vector<Predicate*> predicate, std::string end)
{
    std::cout << predicate.size() << "):\n";
    for (unsigned int i = 0; i < predicate.size(); ++i)
    {
        std::cout << "  " << predicate[i]->id << "(";
        for (unsigned int j = 0; j < predicate[i]->parameters.size(); ++j)
        {
            if (j == 0) std::cout << predicate[i]->parameters[j]->p;
            else std::cout << "," << predicate[i]->parameters[j]->p;
        }
        std::cout << end;
    }
}

void DatalogProgram::printDomain()
{
    std::set <std::string> domain;

    for (unsigned int i = 0; i < facts.size(); ++i)
    {
        for (unsigned int j = 0; j < facts[i]->parameters.size(); ++j)
        {
            domain.insert(facts[i]->parameters[j]->p);
        }
    }
    std::cout << domain.size() << "):\n";

    for (auto p : domain)
    {
        std::cout << "  " << p << std::endl;
    }

}

