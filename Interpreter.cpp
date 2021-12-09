//
// Created by Elliot Silveira on 10/24/21.
//

#include "Interpreter.h"

void Interpreter::interpretThisBaby()
{
    //
    // Add Schemes to Relations
    //
    for (Predicate *scheme: datalog->schemes)
    {
        database->addRelation(scheme->id, getParameters(scheme->parameters));
    }

    //
    // Add Fact values to corresponding Relation tuples
    //
    for (Predicate *fact: datalog->facts)
    {
        Relation *rel = database->relations.find(fact->id)->second;
        rel->addTuple(getParameters(fact->parameters));
    }

    //
    // Evaluate Rules
    //
    // Define new Relation status and number of loops passed through
    bool newRelation = true;
    int ruleCount = 0;

    graphs.grapher(datalog);
    graphs.printFwdList();
//    graphs.printRevList();
    graphs.depthFirstSearch();
//    graphs.printPostOrder();
    graphs.build_a_tree_workshop();
//    graphs.printForest();

    std::cout << "Rule Evaluation\n";

    for (auto list : graphs.redWoods)
    {
        // create a temporary relations to find and hold schemes
        Relation *tempRel;
        Relation *interRel;
        newRelation = true;
        ruleCount = 0;

        if (list.count(-1) || list.size() > 1)
        {
            list.erase(-1);
            std::cout << "SCC: " << printList(list).str() << std::endl;
            while (newRelation)
            {
                ruleCount++;
                newRelation = false;
                for (auto index : list)
                {
                    Rule *rule = datalog->rules[index];
                    // Find the original relation where the schemes will be stored
                    Relation *dbRel = database->relations.find(rule->headPredicate->id)->second;

                    std::vector<int> indices;
                    for (Predicate *bod: rule->bodyPredicates)
                    {
                        //
                        // Evaluate Predicates
                        //
                        // Create temp relation with body predicate parameters and head predicate id (easier for later printing)
                        tempRel = new Relation(rule->headPredicate->id, bod->parameters);
                        tempRel->tuples = evaluatePredicate(bod, false)->tuples;

                        // If looking at the first body predicate interRel = tempRel b/c don't have to Relations to join yet
                        if (rule->bodyPredicates[0] == bod)
                        { interRel = tempRel; }
                        else
                        {
                            //
                            // Join
                            //
                            // Create new header and located indices that need to be merged in the join
                            bool match = false;
                            std::vector<std::pair<int, int>> headIndices;

                            for (size_t i = 0; i < bod->parameters.size(); i++)
                            {
                                for (size_t j = 0; j < interRel->header->head->values.size(); ++j)
                                {
                                    if (bod->parameters[i]->p == interRel->header->head->values[j])
                                    {
                                        headIndices.emplace_back(i, j);
                                        match = true;
                                    }
                                }
                                if (!match)
                                {
                                    interRel->header->head->values.push_back(bod->parameters[i]->p);
                                }
                                match = false;
                            }
                            interRel->tuples = interRel->join(tempRel, headIndices);
                        }
                    }

                    //
                    // Project/Rename
                    //
                    // Identify indices corresponding to parameters in head predicate to pass to project function
                    for (Parameter *param: rule->headPredicate->parameters)
                    {
                        for (size_t i = 0; i < interRel->header->head->values.size(); ++i)
                        {
                            if (param->p == interRel->header->head->values[i])
                            { indices.push_back(i); }
                        }
                    }
                    interRel = interRel->project(indices);
                    interRel = interRel->rename(dbRel->header->head->values);

                    //
                    // Union
                    //
                    for (auto it = interRel->tuples.begin(); it != interRel->tuples.end();)
                    {
                        // Inserting a range of values into a set has no return value. Have to iterate one by one in order to
                        // compare in an if statement
                        if (dbRel->tuples.insert(*it).second)
                        {
                            newRelation = true;
                            ++it;
                        }
                            // Make sure to erase the tuple and then iterate to the next (post-increment operator)
                        else
                        { interRel->tuples.erase(it++); }
                    }
                    interRel->ruleToString(rule);
                }
            }
        }
        else
        {
            std::cout << "SCC: R" << *list.begin() << std::endl;
            Rule *rule = datalog->rules[*list.begin()];
            // Find the original relation where the schemes will be stored
            Relation *dbRel = database->relations.find(rule->headPredicate->id)->second;

            std::vector<int> indices;
            for (Predicate *bod: rule->bodyPredicates)
            {
                //
                // Evaluate Predicates
                //
                // Create temp relation with body predicate parameters and head predicate id (easier for later printing)
                tempRel = new Relation(rule->headPredicate->id, bod->parameters);
                tempRel->tuples = evaluatePredicate(bod, false)->tuples;

                // If looking at the first body predicate interRel = tempRel b/c don't have to Relations to join yet
                if (rule->bodyPredicates[0] == bod)
                { interRel = tempRel; }
                else
                {
                    //
                    // Join
                    //
                    // Create new header and located indices that need to be merged in the join
                    bool match = false;
                    std::vector<std::pair<int, int>> headIndices;

                    for (size_t i = 0; i < bod->parameters.size(); i++)
                    {
                        for (size_t j = 0; j < interRel->header->head->values.size(); ++j)
                        {
                            if (bod->parameters[i]->p == interRel->header->head->values[j])
                            {
                                headIndices.emplace_back(i, j);
                                match = true;
                            }
                        }
                        if (!match)
                        {
                            interRel->header->head->values.push_back(bod->parameters[i]->p);
                        }
                        match = false;
                    }
                    interRel->tuples = interRel->join(tempRel, headIndices);
                }
            }

            //
            // Project/Rename
            //
            // Identify indices corresponding to parameters in head predicate to pass to project function
            for (Parameter *param: rule->headPredicate->parameters)
            {
                for (size_t i = 0; i < interRel->header->head->values.size(); ++i)
                {
                    if (param->p == interRel->header->head->values[i])
                    { indices.push_back(i); }
                }
            }
            interRel = interRel->project(indices);
            interRel = interRel->rename(dbRel->header->head->values);

            //
            // Union
            //
            for (auto it = interRel->tuples.begin(); it != interRel->tuples.end();)
            {
                // Inserting a range of values into a set has no return value. Have to iterate one by one in order to
                // compare in an if statement
                if (dbRel->tuples.insert(*it).second)
                {
                    newRelation = true;
                    ++it;
                }
                    // Make sure to erase the tuple and then iterate to the next (post-increment operator)
                else
                { interRel->tuples.erase(it++); }
            }
            interRel->ruleToString(rule);
            ruleCount++;
        }
        std::cout << ruleCount << " passes: " << printList(list).str() << std::endl;
    }

    //
    // Evaluate Queries
    //
    std::cout << "\nQuery Evaluation\n";
    for (Predicate *q: datalog->queries)
    {
        Relation* temp = evaluatePredicate(q, true);
        temp->queryToString(q);
    }
}

/**
 * @varMap maps the variables and the FIRST index in which they appear in the query
 * @indices vector of all of the indexes that contain variables and should be kept after the project function is called
 * @attributes contains all of the variable names in order for use in the rename function
 * @param q the query being evaluated
 * @return the resulting relation
 */
Relation* Interpreter::evaluatePredicate(Predicate* q, bool isQuery)
{
    std::map<std::string, int> varMap;
    std::vector<int> indices;
    std::vector<std::string> attributes;

    // find the correct Relation
    Relation* rel = database->relations.find(q->id)->second;

    // Select
    for (size_t i = 0; i < q->parameters.size(); ++i) {
        std::string p = q->parameters[i]->p;
        /**
         * I am creating a lot of new Relations but who cares about space
         */
        if (p[0] == '\'') rel = rel->select(i, p);
        else if (varMap.find(p) != varMap.end())
        {
            auto tempMap = varMap.find(p);
            rel = rel->select(tempMap->second, i);
        }
        else
        {
            attributes.push_back(p);
            indices.push_back(i);
            varMap.insert(std::pair<std::string ,int>(p, i));
        }
    }

    if (!rel->tuples.empty())
    {
        // Project
        if (isQuery) {rel = rel->project(indices);}

        // Rename
        rel = rel->rename(attributes);
    }
    return rel;
}

std::vector<std::string> Interpreter::getParameters(std::vector<Parameter *> vector)
{
    std::vector<std::string> parameters;
    for (Parameter *parameter: vector)
    { parameters.push_back(parameter->p); }
    return parameters;
}


void Interpreter::toString() const
{
    std::cout << "Success!\n" << "Schemes(";
    datalog->print("schemes");
    std::cout << "Facts(";
    datalog->print("facts");
    std::cout << "Rules(";
    datalog->printRule();
    std::cout << "Queries(";
    datalog->print("queries");
    std::cout << "Domain(";
    datalog->printDomain();
}