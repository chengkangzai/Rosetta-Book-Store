//
// Created by Cheng Kang Ching on 25/04/2021.
//

using namespace std;
#ifndef ROSETTA_BOOK_STORE_INVALIDINPUT_H
#define ROSETTA_BOOK_STORE_INVALIDINPUT_H

class InvalidInput : virtual public exception {

protected:
    string error_message;      ///< Error message

public:

    /** Constructor (C++ STL string, int, int).
     *  @param msg The error message
     */
    explicit
    InvalidInput(const string &msg) :
            error_message(msg) {}

    /** Destructor.
     *  Virtual to allow for subclassing.
     */
    virtual ~InvalidInput() throw() {}

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *  is in possession of the Except object. Callers must
     *  not attempt to free the memory.
     */
    virtual const char *what() const throw() {
        return error_message.c_str();
    }
};

#endif //ROSETTA_BOOK_STORE_INVALIDINPUT_H
