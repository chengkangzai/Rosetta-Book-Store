#include "Query/BookQuery.h"
#include "Query/PurchaseQuery.h"


int getFirstLevelOption(int firstLevelOption);

void handleFirstLevelOption(int firstLevelOption);

void handleFilterBook(int temp);

using namespace std;

auto bookQuery = BookQuery();
auto purchaseQuery = PurchaseQuery();

int main() {
//    BookQuery::test();
//    cout << "------------------------------------------------------------\n";
//    PurchaseQuery::test();

    int firstLevelOption;

    do {
        firstLevelOption = getFirstLevelOption(firstLevelOption);
        handleFirstLevelOption(firstLevelOption);
    } while (firstLevelOption <= 6);
    return 0;

}

void handleFirstLevelOption(int firstLevelOption) {
    int secondLevelOption;
    switch (firstLevelOption) {
        case 1:
            cout << "1. Add Book " << endl
                 << "2. Read Book " << endl
                 << "3. Search Book " << endl
                 << "4. Filter Book " << endl
                 << "5. Update Book " << endl
                 << "6. Sort Book " << endl
                 << "7. Delete Book " << endl
                 << "8. Exit Program " << endl
                 << "9. Back " << endl;
            cin >> secondLevelOption;
            cin.ignore();
            fflush(stdout);
            switch (secondLevelOption) {
                case 1:
                    bookQuery.create(Book().getFromCli());
                    break;
                case 2:
                    bookQuery.head->printNode();
                    break;
                case 3:
                    int searchQuery;
                    cout << "Enter Book ID " << endl;
                    cin >> searchQuery;
                    cin.ignore();
                    fflush(stdout);

                    try {
                        bookQuery.where(BookQuery::ID, searchQuery).print();
                    } catch (ModalNotFoundException exception) {
                        cout << "The ID you enter do not have associated Book in our Data base \n";
                    }
                    break;
                case 4:
                    cout << "Filter Book Based on : " << endl
                         << "1. Category " << endl
                         << "2. Genre " << endl;
                    int temp;
                    cin >> temp;

                    handleFilterBook(temp);
                    break;
                case 5:
                    int bookID;
                    cout << "Enter Book ID that you want to update " << endl;
                    cin >> bookID;
                    cin.ignore();
                    fflush(stdout);

                    try {
                        auto target = bookQuery.where(BookQuery::ID, bookID);
                        bookQuery.update(Book().getFromCli(), target.id - 1);
                    } catch (ModalNotFoundException modalNotFoundException) {
                        cout << "The ID you enter do not have associated Book in our Data base \n";
                    }

                    break;
                case 6:
                    cout << "Sort by Total Quantity of the Books" << endl;
                    bookQuery.insertionSort()->printNode();
                    break;
                case 7:
                    int bookId;
                    cout << "Enter Book ID that you want to Delete " << endl;
                    cin >> bookId;
                    cin.ignore();
                    fflush(stdout);

                    try {
                        auto target = bookQuery.where(BookQuery::ID, bookId);
                        bookQuery.del(target.id);
                    } catch (ModalNotFoundException modalNotFoundException) {
                        cout << "The ID you enter do not have associated Book in our Data base \n";
                    }

                    break;
                case 8:
                    exit(1);
            }

            break;
        case 2:
            cout << "1. Add Purchase " << endl
                 << "2. View Purchase " << endl
                 << "3. Sort Purchase " << endl
                 << "4. Search Purchase " << endl
                 << "5. Exit " << endl
                 << "6. Back " << endl;
            cin >> secondLevelOption;
            cin.ignore();
            fflush(stdout);
            switch (secondLevelOption) {
                case 1:
                    purchaseQuery.create(Purchase().getFromCli());
                    break;
                case 2:
                    cout << "Print all purchase from newest to oldest";
                    purchaseQuery.printReverse();
                    break;
                case 3:
                    cout << "Print all purchase sort by Total price";
                    purchaseQuery.sortByTotalPrice();
                    break;
                case 4:
                    cout << "Enter Purchase ID";
                    int purchaseId;
                    cin >> purchaseId;

                    try {
                        purchaseQuery.where(PurchaseQuery::ID, purchaseId).print();
                    } catch (ModalNotFoundException modalNotFoundException) {
                        cout << "The ID you enter do not have associated Book in our Data base \n";
                    }
                    break;
                case 5:
                    exit(1);
            }
            break;
        case 3:
            cout << "Performing Unit Testing ...  \n";
            BookQuery::test();
            cout << "------------------------------------------------------------\n";
            PurchaseQuery::test();
            break;
        case 4:
            cout << "Lazy huh ? Initialize Prefilled data \n";
            bookQuery = BookQuery().init();
            purchaseQuery = PurchaseQuery().init();
            break;
        case 5:
            cout << "Rosetta Book Store v1.0.0" << endl
                 << "Produced by Ching Cheng Kang (TP051436) and Chan Chin Wei (TP051429)" << endl
                 << "This is an assignment project for learning Data Structure and Algorithm in Asia Pacific University."
                 << endl;
            break;
        default:
            exit(1);
    }
}

void handleFilterBook(int temp) {
    switch (temp) {
        case 1:
            cout << "Pick a Genre" << endl;
            cout << "1. FANTASY" << endl;
            cout << "2. HISTORICAL" << endl;
            cout << "3. REALISTIC" << endl;
            cout << "4. SCIENCE" << endl;
            cout << "5. NARRATIVE" << endl;
            cout << "6. BIOGRAPHY" << endl;
            cout << "7. PERIODICALS" << endl;
            cout << "8. SELF_HELP" << endl;
            cout << "9. REFERENCE" << endl;
            int genreTemp;
            cin >> genreTemp;
            try {

                switch (genreTemp) {
                    case 1:
                        bookQuery.wheres(BookQuery::GENRE, Book::FANTASY)->printNode();
                        break;
                    case 2:
                        bookQuery.wheres(BookQuery::GENRE, Book::HISTORICAL)->printNode();
                        break;
                    case 3:
                        bookQuery.wheres(BookQuery::GENRE, Book::REALISTIC)->printNode();
                        break;
                    case 4:
                        bookQuery.wheres(BookQuery::GENRE, Book::SCIENCE)->printNode();
                        break;
                    case 5:
                        bookQuery.wheres(BookQuery::GENRE, Book::NARRATIVE)->printNode();
                        break;
                    case 6:
                        bookQuery.wheres(BookQuery::GENRE, Book::BIOGRAPHY)->printNode();
                        break;
                    case 7:
                        bookQuery.wheres(BookQuery::GENRE, Book::PERIODICALS)->printNode();
                        break;
                    case 8:
                        bookQuery.wheres(BookQuery::GENRE, Book::SELF_HELP)->printNode();
                        break;
                    case 9:
                        bookQuery.wheres(BookQuery::GENRE, Book::REFERENCE)->printNode();
                        break;
                    default:
                        throw InvalidInput("Invalid Input");
                }
            } catch (InvalidInput invalidInput) {
                cout << invalidInput.what();
            } catch (ModalNotFoundException modalNotFoundException) {
                cout << "The ID you enter do not have associated Book in our Data base \n";
            }
            break;
        case 2:
            cout << "1. NON_FICTION" << endl;
            cout << "2. FICTION" << endl;
            int categoryTemp;
            cin >> categoryTemp;
            try {
                switch (categoryTemp) {
                    case 1:
                        bookQuery.wheres(BookQuery::CATEGORY, Book::NON_FICTION)->printNode();
                        break;
                    case 2:
                        bookQuery.wheres(BookQuery::CATEGORY, Book::FICTION)->printNode();
                        break;
                    default:
                        throw InvalidInput("Invalid Input");
                }
            } catch (InvalidInput invalidInput) {
                cout << invalidInput.what();
            } catch (ModalNotFoundException modalNotFoundException) {
                cout << "The ID you enter do not have associated Book in our Data base \n";
            }
            break;
        default:
            throw InvalidInput("Invalid Input");
    }
}

/**
 * https://stackoverflow.com/questions/40984752/c-input-string-with-spaces
 * @param firstLevelOption
 * @return
 */
int getFirstLevelOption(int firstLevelOption) {
    cout << "Welcome to Rosetta Book Store !" << endl
         << "Choose your Option! " << endl
         << "1. Inventory(Book) Management  " << endl
         << "2. Purchase Management  " << endl
         << "3. Perform Unit Testing  " << endl
         << "4. Continue with prefilled data  " << endl
         << "5. About this Software  " << endl
         << "6. Exit !  " << endl;
    cin >> firstLevelOption;
    cin.ignore();
    fflush(stdout);
    return firstLevelOption;
}
