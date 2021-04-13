//
// Created by CCK on 2021-04-13.
//

#ifndef ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H
#define ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H

#include <iostream>

class InvalidQueryType : public std::exception {
public:
    InvalidQueryType(const char *msg) : std::exception(msg) {
    }
};


#endif //ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H
