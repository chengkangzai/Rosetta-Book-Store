//
// Created by CCK on 2021-04-13.
//

#ifndef ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H
#define ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H

#include <iostream>

class InvalidQueryType : virtual public std::exception {

protected:
    std::string error_message;      ///< Error message

public:

    /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     */
    explicit
    InvalidQueryType(const std::string &msg) :
            error_message(msg) {}

    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~InvalidQueryType() throw() {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char *what() const throw() {
        return error_message.c_str();
    }
};



#endif //ROSETTA_BOOK_STORE_INVALIDQUERYTYPE_H
