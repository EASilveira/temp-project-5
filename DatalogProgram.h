//
// Created by Elliot Silveira on 9/27/21.
//

#ifndef PROJECT_2_DATALOGPROGRAM_H
#define PROJECT_2_DATALOGPROGRAM_H

#include <iostream>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    DatalogProgram() = default;
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;

    Rule* newHead(std::string description)
    {
        Predicate* head = new Predicate(description);
        Rule* rule = new Rule(head);
        rules.push_back(rule);
        return rule;
    }

    Predicate* newScheme(std::string description)
    {
        Predicate* scheme = new Predicate(description);
        schemes.push_back(scheme);
        return scheme;
    }

    Predicate* newFact(std::string description)
    {
        Predicate* fact = new Predicate(description);
        facts.push_back(fact);
        return fact;
    }

    Predicate* newQuery(std::string description)
    {
        Predicate* query = new Predicate(description);
        queries.push_back(query);
        return query;
    }
    void print(std::string type)
    {
        if (type == "schemes") toString(schemes, ")\n");
        else if (type == "facts") toString(facts, ").\n");
        else if (type == "queries") toString(queries, ")?\n");
    }
    void toString(std::vector<Predicate*> predicate, std::string end);

    void printRule()
    {
        std::cout << rules.size() << "):\n";
        for (unsigned int i = 0; i < rules.size(); i++) { rules[i]->toString(); }
    }

    void printDomain();
};


#endif //PROJECT_2_DATALOGPROGRAM_H
