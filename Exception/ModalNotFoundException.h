//
// Created by CCK on 2021-04-03.
//

#ifndef ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H
#define ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H

#include <iostream>

class ModalNotFoundException : public std::exception {

public:
    ModalNotFoundException(const char *msg) : std::exception(msg) {
    }

};


#endif //ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H
