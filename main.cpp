#include "Query/BookQuery.h"


using namespace std;

int main() {
    BookQuery::test();


//    auto bq = BookQuery().init();
//
//    bq->create(Book(11, "HARRY POTTER", "J. K. ROWLING", Book::FANTASY, Book::FICTION,
//                    "9780747532743", 50, 56.80, true));
//    try {
//        bq->wheres(bq->TITLE, "HARRY POTTER")->printNode();
//    } catch (ModalNotFoundException &exception) {
//        cout << exception.what();
//    }

    return 0;
}
