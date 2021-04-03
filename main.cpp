#include <iostream>
#include "Query/BookQuery.h"
#include <cassert>


using namespace std;

int main() {
    BookQuery().test();
//    auto bookQ = BookQuery().init();
//    cout << "-------------------------------------------------- \n";
//    cout << "TEST 1 : Update Record number 1 : ";
//    auto target = bookQ->where(bookQ->ID, 1);
//    bookQ->update(Book(1, "DATA STRUCTURE AND ALGORITHM", "Rolin Jackson", "FANTASY",
//                       "FICTION", "9780747532743", 70, 76.80, true),
//                  target.id - 1);
//
//    assert(bookQ->where(bookQ->ID, 1).title == "DATA STRUCTURE AND ALGORITHM");
//    cout << "PASSED \n";
//    cout << "-------------------------------------------------- \n \n";
//
//    cout << "-------------------------------------------------- \n";
//    cout << "TEST 2 : Delete Record ID 2 : ";
//    auto target2 = bookQ->where(bookQ->ID, 2);
//    assert(bookQ.)
//    cout << "-------------------------------------------------- \n \n";

//    bookQ->where(bookQ->AUTHOR, "JAY ASHER").print();
//    bookQ->where(bookQ->INDEX, 5).print();
//
//    bookQ->head->printNode();

    return 0;
}
