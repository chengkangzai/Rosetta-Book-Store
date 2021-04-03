#include <iostream>
#include "Query/BookQuery.h"

using namespace std;


// Driver program to test above functions
int main() {
    struct Node *a = NULL;
    auto s = BookQuery().init();


    printf("Linked List before sorting \n");
//    s->printAll();

    s->insertionSort();

    printf("\nLinked List after sorting \n");
//    s->printAll();

    return 0;
}