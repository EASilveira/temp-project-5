//
// Created by Elliot Silveira on 9/28/21.
//

#ifndef PROJECT_2_RULE_H
#define PROJECT_2_RULE_H

#include "Predicate.h"

class Rule {
public:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
    Rule(Predicate* hPred) { headPredicate = hPred; }

    void newParameter(std::string parameter) { headPredicate->newParameter(parameter); }
    Predicate* newBody(std::string description)
    {
        Predicate* body = new Predicate(description);
        bodyPredicates.push_back(body);
        return body;
    }

    Predicate* getHead() { return headPredicate; }

    void toString();

};


#endif //PROJECT_2_RULE_H
