#include "Query/BookQuery.h"
#include "Query/PurchaseQuery.h"


using namespace std;

int main() {
//    BookQuery::test();

    auto current = PurchaseQuery().init()->sortByTotalPrice();

    while (!current.empty()) {
        current.top().print();
        current.pop();
    }
    return 0;
}
