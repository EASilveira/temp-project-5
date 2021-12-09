//
// Created by Elliot Silveira on 10/24/21.
//

#ifndef PROJECT_3_DATABASE_H
#define PROJECT_3_DATABASE_H
#include <iostream>
#include <map>
#include "Relation.h"

class Database {
public:
    Database() = default;
    std::map<std::string, Relation*> relations;

    void addRelation(std::string name, std::vector<std::string> attributes)
    {
        Relation* relation = new Relation(name, attributes);
        relations.insert(std::pair<std::string ,Relation*>(name, relation));
    }

};


#endif //PROJECT_3_DATABASE_H
