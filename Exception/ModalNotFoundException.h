//
// Created by CCK on 2021-04-03.
//

#ifndef ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H
#define ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H

#include <iostream>

using namespace std;

//https://riptutorial.com/cplusplus/example/23640/custom-exception
class ModalNotFoundException : virtual public exception {

protected:
    string error_message;      ///< Error message

public:

    /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     */
    explicit
    ModalNotFoundException(const string &msg) :
            error_message(msg) {}

    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~ModalNotFoundException() throw() {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char *what() const throw() {
        return error_message.c_str();
    }
};


#endif //ROSETTA_BOOK_STORE_MODALNOTFOUNDEXCEPTION_H
