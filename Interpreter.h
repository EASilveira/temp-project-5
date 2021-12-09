//
// Created by Elliot Silveira on 10/24/21.
//

#ifndef PROJECT_3_INTERPRETER_H
#define PROJECT_3_INTERPRETER_H

#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Graph.h"
#include "DatalogProgram.h"
#include "Parser.h"
#include "Database.h"
/**
 * Link between Datalog and Database classes
 *
 * stuffs - contains the attributes of Schemes or values from Facts
 */
class Interpreter {

public:
    DatalogProgram* datalog;
    Graph graphs;
    Database* database = new class Database;
    std::vector<std::string> stuffs;
    std::stringstream ss;

    Interpreter(Parser* data) {datalog = data->getData();}
    void toString() const;
    void interpretThisBaby();
    Relation* evaluatePredicate(Predicate*, bool);
    static std::vector<std::string> getParameters(std::vector<Parameter*> vector);
    std::stringstream printList(std::set<int> list)
    {
        std::stringstream ss;
        for (auto rule : list)
        {
            if (rule == *list.begin()) { ss << "R" << rule; }
            else { ss << ",R" << rule; }
        }
        return ss;
    }
};


#endif //PROJECT_3_INTERPRETER_H
