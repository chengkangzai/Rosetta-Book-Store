#include "Query/BookQuery.h"
#include "Query/PurchaseQuery.h"


using namespace std;

int main() {
    BookQuery::test();
    cout << "------------------------------------------------------------\n";
    PurchaseQuery::test();
    return 0;
}
