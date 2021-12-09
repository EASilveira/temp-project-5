//
// Created by Elliot Silveira on 12/7/21.
//

#include "Graph.h"

void Graph::build_a_tree_workshop()
{
    visited.clear();
//    std::vector<int> postMalones = postOrder;
    std::vector<int> postMalones;
    for (int i = postOrder.size() - 1; i > -1; i--)
    {
        postMalones.push_back(postOrder[i]);
    }
//    std::reverse(postMalones.begin(), postMalones.end());
    std::set<int> temp;

    redWoods.push_back(build_a_tree(postMalones[0], temp));
    while (visited.size() != fwdGraph.size())
    {
        //Check for lowest number not in set
        for (auto posty : postMalones)
        {
            if (!visited.count(posty)) {
//                std::cout << "Missing " << expected << std::endl;
                redWoods.push_back(build_a_tree(posty, temp));
                break;
            }
        }
    }
    return;
}

std::set<int> Graph::build_a_tree(int posty, std::set<int> temp)
{
    visited.insert(posty);
    temp.insert(posty);
    for (int index : fwdGraph.find(posty)->second)
    {
        if (visited.insert(index).second)
        {
            temp = build_a_tree(index, temp);
        }
        if (index == posty || temp.size() > 1) temp.insert(-1);
    }
    return temp;
}

void Graph::depthFirstSearch()
{
    postOrderer(0);
    while (visited.size() != fwdGraph.size())
    {
        int size = fwdGraph.size();
        auto it = visited.begin();
        //Check for lowest number not in set
        for (int expected = 0; expected < size; ++it, ++expected)
        {
            if (*it != expected) {
//                std::cout << "Missing " << expected << std::endl;
                postOrderer(expected);
                break;
            }
        }
    }
}

void Graph::postOrderer(int rule)
{
    visited.insert(rule);
    for (int index : revGraph.find(rule)->second)
    {
        if (visited.insert(index).second)
        {
            postOrderer(index);
        }
    }
    postOrder.push_back(rule);
    return;
}

void Graph::grapher(DatalogProgram* datalog)
{
    for (size_t i = 0; i < datalog->rules.size(); i++)
    {
        fwdGraph[i];
        revGraph[i];
        for (Predicate* bod : datalog->rules[i]->bodyPredicates)
        {
            for (size_t j = 0; j < datalog->rules.size(); j++)
            {
                if (bod->id == datalog->rules[j]->headPredicate->id)
                {
                    fwdGraph[i].insert(j);
                    revGraph[j].insert(i);
                }
            }
        }
    }
}

void Graph::printFwdList()
{
    std::map<int, std::set<int>>::iterator it = fwdGraph.begin();

    std::cout << "Dependency Graph" << "\n";
    for (it=fwdGraph.begin(); it!=fwdGraph.end(); ++it)
    {
        std::cout << "R" << it->first << ":";
        std::set<int>::iterator index = it->second.begin();
        while (index != it->second.end())
        {
            if (index == it->second.begin())
            {
                std::cout << "R" << *index;
            } else
            {
                std::cout << ",R" << *index;
            }
            ++index;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Graph::printRevList()
{
    std::map<int, std::set<int>>::iterator it = revGraph.begin();

    std::cout << "\n\nReverse Dependency Graph" << "\n";
    for (it=revGraph.begin(); it!=revGraph.end(); ++it)
    {
        std::cout << "R" << it->first << ":";
        std::set<int>::iterator index = it->second.begin();
        while (index != it->second.end())
        {
            if (index == it->second.begin())
            {
                std::cout << "R" << *index;
            }
            else
            {
                std::cout << ",R" << *index;
            }
            ++index;
        }
        std::cout << std::endl;
    }
}

void Graph::printPostOrder()
{
    std::cout << "PostOrder:\n";
    for (auto index : postOrder)
    {
        std::cout << "R" << index << ", ";
    }
    std::cout << std::endl;
}

void Graph::printForest()
{
    std::cout << "\nYour Forest My Liege: " << "\n";
    for (auto tree : redWoods)
    {
        for (auto branch : tree)
        {
            std::cout << branch << ", ";
        }
        std::cout << std::endl;
    }
}