//
// Created by Elliot Silveira on 10/24/21.
//

#ifndef PROJECT_3_TUPLE_H
#define PROJECT_3_TUPLE_H
#include <iostream>
#include <vector>
/**
 * stuffs - contains a vector of Header attributes or Fact values
 */
class Tuple {

public:
    std::vector<std::string> values;

    Tuple(std::vector<std::string> stuffs) {values = stuffs;}
    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }

    void addValue (std::string attributes) {values.push_back(attributes);}
};


#endif //PROJECT_3_TUPLE_H
