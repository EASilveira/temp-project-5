//
// Created by Elliot Silveira on 10/24/21.
//

#ifndef PROJECT_3_HEADER_H
#define PROJECT_3_HEADER_H
#include <iostream>
#include <vector>
#include "Tuple.h"

class Header {

public:
    Tuple* head;
    Header(std::vector<std::string> attributes) {head = new Tuple(attributes);}


};


#endif //PROJECT_3_HEADER_H
