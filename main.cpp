#include <iostream>
#include "Query/BookQuery.h"

using namespace std;

int main() {
    auto bookQ = BookQuery().init();
//    cout << bookQ->get(0).toString() << "\n";
//    bookQ->update(
//            Book(1, "DATA STRUCTURE AND ALGORITHM", "Rolin Jackson", "FANTASY", "FICTION", "9780747532743", 70, 76.80,
//                 true), 0);
//    cout << bookQ->get(0).toString() << "\n";

//    cout << bookQ->printAll() << "\n";
    bookQ->del(1);
    cout << bookQ->printAll() << "\n";


    return 0;
}
