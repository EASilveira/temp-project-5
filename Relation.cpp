//
// Created by Elliot Silveira on 10/24/21.
//

#include "Relation.h"
#include <sstream>

std::set<Tuple> Relation::join(Relation *tempRel, const std::vector<std::pair<int,int>>& indices)
{
    std::set<Tuple> interTup = tuples;
    std::set<Tuple> tempTup = tempRel->tuples;
    std::set<Tuple> resSet;

    //Begin looping through to join vectors
    if (indices.size() > 1)
    {
        for (auto t1: tempTup)
        {
            for (auto t2: interTup)
            {
                if (isJoinable(t1.values, t2.values, indices))
                {
                    resSet.insert(joinVectors(t1.values, t2.values, indices));
                }
            }
        }
    }
    else if (indices.size() == 1)
    {
        for (auto t1: tempTup)
        {
            for (auto t2: interTup)
            {
                if (t1.values[indices.at(0).first] == t2.values[indices.at(0).second])
                {
                    resSet.insert(joinVectors(t1.values, t2.values, indices.at(0).first));
                }
            }
        }
    }
    // Cross product (i.e. no columns to merge)
    else
    {
        for (auto t1: tempTup)
        {
            for (auto t2: interTup)
            {
                resSet.insert(joinVectors(t1.values, t2.values));
            }
        }
    }
    return resSet;
}

bool Relation::isJoinable(std::vector<std::string> t1, std::vector<std::string> t2, const std::vector<std::pair<int, int>> indices)
{
    for (auto i: indices)
    {
        if (t1[i.first] != t2[i.second]) {return false;}
    }
    return true;
}

std::vector<std::string> Relation::joinVectors(std::vector<std::string> t1, std::vector<std::string> t2,
                                               std::vector<std::pair<int, int>> indices)
{
    for (size_t i = 0; i < t1.size(); ++i)
    {
        int index = i;
        // Add every index of t1 that is not in indices (the joining point indices)
        if (index == indices[0].first) {indices.erase(indices.begin());}
        else {t2.push_back(t1[index]);}
    }
    return t2;
}

std::vector<std::string> Relation::joinVectors(std::vector<std::string> t1, std::vector<std::string> t2, const int index)
{
    t1.erase(t1.begin() + index);
    t2.insert(t2.end(), t1.begin(), t1.end());
    return t2;
}

std::vector<std::string> Relation::joinVectors(std::vector<std::string> t1, std::vector<std::string> t2)
{
    t2.insert(t2.end(), t1.begin(), t1.end());
    return t2;
}

Relation *Relation::project(const std::vector<int>& indices)
{
    auto *copy = new Relation(name, header->head->values);
    for (Tuple t: tuples)
    {
        std::vector<std::string> newTuple;
        for (int index: indices)
        {
            newTuple.push_back(t.values[index]);
        }
        copy->addTuple(newTuple);
    }
    return copy;
}

Relation *Relation::select(int index, const std::string &value)
{
    auto *copy = new Relation(name, header->head->values);
    for (Tuple t: tuples)
    {
        if (value == t.values[index])
        {
            copy->addTuple(t.values);
        }
    }
    return copy;
}

Relation *Relation::select(int index1, int index2)
{
    auto *copy = new Relation(name, header->head->values);
    for (Tuple t: tuples)
    {
        if (t.values[index1] == t.values[index2])
        {
            copy->addTuple(t.values);
        }
    }
    return copy;
}

void Relation::ruleToString(Rule *rule)
{

    std::stringstream ss;

    // Print Head Predicate
    ss << name << "(";
    for (size_t i = 0; i < rule->headPredicate->parameters.size(); ++i)
    {
        std::string p = rule->headPredicate->parameters[i]->p;
        if (i < rule->headPredicate->parameters.size() - 1) ss << p << ",";
        else ss << p << ") :- ";
    }

    // Print Body Predicates
    for (size_t i = 0; i < rule->bodyPredicates.size(); ++i)
    {
        Predicate *pred = rule->bodyPredicates[i];
        ss << pred->id << "(";
        for (size_t j = 0; j < pred->parameters.size(); ++j)
        {
            std::string p = pred->parameters[j]->p;
            if (j < pred->parameters.size() - 1) ss << p << ",";
            else ss << p << ")";
        }
        if (i < rule->bodyPredicates.size() - 1)
        { ss << ","; }
        else
        { ss << ".\n"; }
    }

    // Print Resulting Schemes in new Relation
    for (Tuple t: tuples)
    {
        for (size_t i = 0; i < header->head->values.size(); ++i)
        {
            if (i == 0) ss << "  ";
            if (i < header->head->values.size() - 1)
            {
                ss << header->head->values[i] << "=" << t.values[i] << ", ";
            } else ss << header->head->values[i] << "=" << t.values[i] << "\n";
        }
    }

    std::cout << ss.str();
    ss.str(std::string());
}

void Relation::queryToString(const Predicate* q)
{
    std::cout << q->id << "(";

    for (size_t i = 0; i < q->parameters.size(); ++i)
    {
        std::string p = q->parameters[i]->p;
        if (i < q->parameters.size() - 1) std::cout << p << ",";
        else std::cout << p << ")? ";
    }
    if (!tuples.empty())
    {
        std::cout << "Yes(" << tuples.size() << ")\n";
        for (Tuple t: tuples)
        {
            for (size_t i = 0; i < header->head->values.size(); ++i)
            {
                if (i == 0) std::cout << "  ";
                if (i < header->head->values.size() - 1)
                {
                    std::cout << header->head->values[i] << "=" << t.values[i] << ", ";
                } else std::cout << header->head->values[i] << "=" << t.values[i] << "\n";
            }
        }
    } else std::cout << "No\n";
}