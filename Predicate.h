//
// Created by Elliot Silveira on 9/27/21.
//

#ifndef PROJECT_2_PREDICATE_H
#define PROJECT_2_PREDICATE_H

#include <iostream>
#include <vector>
#include "Parameter.h"


class Predicate {
private:
public:
    std::string id;
    std::vector<Parameter*> parameters;

    Predicate(std::string passedId) { id = passedId; }

    void newParameter(std::string parameter) { parameters.push_back(new Parameter(parameter)); }
};


#endif //PROJECT_2_PREDICATE_H
