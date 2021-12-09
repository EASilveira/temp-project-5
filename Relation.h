//
// Created by Elliot Silveira on 10/24/21.
//

#ifndef PROJECT_3_RELATION_H
#define PROJECT_3_RELATION_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Header.h"
#include "Rule.h"

class Relation
{

public:
    std::string name;
    Header *header;
    std::set<Tuple> tuples;

    Relation(std::string id, std::vector<std::string> attributes)
    {
        name = id;
        header = new Header(attributes);
    }

    // Used to create relations using the parameters in rule predicates b/c does not have a vector of strings.
    Relation(std::string id, std::vector<Parameter *> parameters)
    {
        name = id;
        std::vector<std::string> attributes;
        for (Parameter *para: parameters) attributes.push_back(para->p);
        header = new Header(attributes);
    }

    Relation *select(int index, const std::string &value);

    Relation *select(int index1, int index2);

    Relation *project(const std::vector<int>& indices);

    bool isJoinable(std::vector<std::string>, std::vector<std::string>, const std::vector<std::pair<int, int>>);

    std::set<Tuple> join(Relation *tempRel, const std::vector<std::pair<int,int>>& indices);

    std::vector<std::string> joinVectors(std::vector<std::string>, std::vector<std::string>, std::vector<std::pair<int, int>>);

    std::vector<std::string> joinVectors(std::vector<std::string>, std::vector<std::string>, const int);

    std::vector<std::string> joinVectors(std::vector<std::string>, std::vector<std::string>);

    Relation *rename(std::vector<std::string> attributes)
    {
        Relation *copy = new Relation(name, attributes);
        copy->tuples = tuples;
        return copy;
    }

    void addTuple(std::vector<std::string> temp)
    { tuples.insert(temp); }

    void ruleToString(Rule *rule);

    void queryToString(const Predicate*);

};


#endif //PROJECT_3_RELATION_H
