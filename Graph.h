//
// Created by Elliot Silveira on 12/7/21.
//

#ifndef PROJECT_5_GRAPH_H
#define PROJECT_5_GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "DatalogProgram.h"

class Graph
{
public:
    std::vector<std::set<int>> redWoods;
    std::map<int, std::set<int>> fwdGraph;
    std::map<int, std::set<int>> revGraph;
    std::vector<int> postOrder;
    std::set<int> visited;

    void grapher(DatalogProgram*);
    void postOrderer(int);
    void depthFirstSearch();
    void printFwdList();
    void printRevList();
    void printPostOrder();
    void printForest();
    void build_a_tree_workshop();
    std::set<int> build_a_tree(int, std::set<int>);
};


#endif //PROJECT_5_GRAPH_H
