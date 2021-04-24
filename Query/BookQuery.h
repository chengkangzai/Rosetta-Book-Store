//
// Created by CCK on 2021-04-02.
//

#ifndef ROSETTA_BOOK_STORE_BOOKQUERY_H
#define ROSETTA_BOOK_STORE_BOOKQUERY_H

#include <iostream>
#include <utility>
#include <cassert>

#include "../Models/Book.h"
#include "../Exception/ModalNotFoundException.h"
#include "../Exception/InvalidQueryType.h"

using namespace std;

class BooksNode {
public:
    BooksNode() = default;

    explicit BooksNode(Book book) : book(move(book)) {
    }

    Book book;
    struct BooksNode *next{};

    BooksNode *printNode() {
        BooksNode *current = this;

        if (current == nullptr) {
            cout << "NULL";
            return this;
        }

        while (current != nullptr) {
            current->book.print();
            current = current->next;
        }
        delete current;
        return this;
    }

    int size() {
        BooksNode *ptr = this;
        int temp = 0;

        while (ptr != nullptr) {
            temp++;
            ptr = ptr->next;
        }

        return temp;
    }
};

class BookQuery {
public:
    struct BooksNode *head = nullptr;

    enum QUERY_TYPE {
        TITLE, ID, AUTHOR, INDEX, CATEGORY, GENRE
    };


    BooksNode *wheres(QUERY_TYPE TYPE, const string &searchQuery) {
        if (TYPE == TITLE)
            return this->searchByTitle(searchQuery);
        if (TYPE == AUTHOR)
            return this->searchByAuthor(searchQuery);

        throw InvalidQueryType("Invalid QUERY_TYPE !");
    }

    BooksNode *wheres(QUERY_TYPE TYPE, enum Book::CATEGORY searchQuery) {
        if (TYPE == CATEGORY)
            return this->searchByCategory(searchQuery);

        throw InvalidQueryType("Invalid QUERY_TYPE !");
    }

    BooksNode *wheres(QUERY_TYPE TYPE, enum Book::GENRE searchQuery) {
        if (TYPE == GENRE)
            return this->searchByGenre(searchQuery);

        throw InvalidQueryType("Invalid QUERY_TYPE !");
    }

    Book where(QUERY_TYPE TYPE, int searchQuery) {
        if (TYPE == ID)
            return this->searchByID(searchQuery);
        if (TYPE == INDEX)
            return this->searchByIndex(searchQuery);
        if (TYPE == AUTHOR || TYPE == TITLE || TYPE == CATEGORY)
            throw InvalidQueryType("QUERY_TYPE not supported ! ps: Author and TITLE with int...?");

        throw InvalidQueryType("Invalid QUERY_TYPE !");
    }

    BookQuery *create(Book book) {
        auto *newNode = new BooksNode(Book(move(book)));

        //check if the book is the first one
        if (head == nullptr) {
            head = newNode;
            return this;
        }

        BooksNode *current = head;
        //Go to the last one (which is null)
        while (current->next != nullptr) {
            current = current->next;
        }
        //Connect the last one with the new Node
        current->next = newNode;
        return this;
    }

    const BookQuery *update(Book newBook, int index) const {
        if (index < 0 || index >= head->size()) {
            throw ("Index out of bound. \n");
        }
        BooksNode *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->book = Book(move(newBook));
        return this;
    }

    /**
     * https://stackoverflow.com/questions/25599343/remove-an-element-from-a-linked-list-in-c/51127711
     * @param bookID that you wanted to delete!
     * @return
     */
    BookQuery *del(int bookID) {
        if (bookID < 0 || bookID >= head->size()) {
            throw ("Index out of bound. \n");
        }
        //Instead of checking it is one, check it its the first index ...
        if (this->where(this->INDEX, 0).id == bookID) {
            head = head->next;
            return this;
        }

        BooksNode *prev = head;
        BooksNode *current = head->next;
        while (current != nullptr) {
            if (current->book.id == bookID) {
                break;
            } else {
                prev = current;
                current = current->next;
            }
        }

        if (current == nullptr) {
            throw ModalNotFoundException("Can't remove value: no match found.\n");
        }

        prev->next = current->next; // link the previous node to the next node
        delete current;

        return this;
    }

    // TODO: Sort by...
    // function to sort a singly linked list using insertion sort
    BooksNode *insertionSort() const {
        struct BooksNode *sorted = nullptr;

        // Traverse the given linked list and insert every BooksNode to sorted
        struct BooksNode *current = head;
        while (current != nullptr) {
            // Store next for next iteration
            struct BooksNode *next = current->next;
            // insert current in sorted linked list
            insertForQuality(&sorted, current);
            // Update current
            current = next;
        }
        return sorted;
    }

    BookQuery *init() {
        this->create(Book(1, "HARRY POTTER", "J. K. ROWLING",
                          Book::FANTASY, Book::FICTION,
                          "9780747532743", 50, 56.80, true));
        this->create(Book(2, "MEIN KAMPF", "ADOLF HITLER",
                          Book::HISTORICAL, Book::FICTION,
                          "9780395925034", 5, 120.50, false));
        this->create(Book(3, "13 REASONS WHY", "JAY ASHER",
                          Book::REALISTIC, Book::FICTION,
                          "9780451479327", 3, 63.20, true));
        this->create(Book(4, "THE INVISIBLE MAN", "H. G. WELLS",
                          Book::SCIENCE, Book::FICTION,
                          "9781512091977", 5, 30.45, true));
        this->create(Book(5, "THE HUNGER GAMES", "SUZANNE COLLINS",
                          Book::NARRATIVE, Book::NON_FICTION,
                          "9780439023481", 9, 124.41, true));
        this->create(Book(6, "I HAVE A DREAM", "MARTIN LUTHER KING JR.",
                          Book::BIOGRAPHY, Book::NON_FICTION,
                          "9780375858871", 30, 100.00, true));
        this->create(Book(7, "CRIME AND PERIODICALS", "NOVA EVERLY",
                          Book::PERIODICALS, Book::NON_FICTION,
                          "9781949202076", 2, 35.9, true));
        this->create(Book(8, "A NEW EARTH", "ECKHART TOLLE",
                          Book::SELF_HELP, Book::NON_FICTION,
                          "9780452289963", 10, 15.00, true));
        this->create(Book(9, "THE HERO WITH A THOUSAND FACES", "JOSEPH CAMPBELL",
                          Book::REFERENCE, Book::NON_FICTION,
                          "9781577315933", 6, 78.00, true));
        return this;
    }

    static void test() {
        auto bookQ = BookQuery().init();

        cout << "TEST 1 : Update Record number 1 \t\t\t\t\t: ";
        auto target = bookQ->where(bookQ->ID, 1);
        bookQ->update(Book(1, "DATA STRUCTURE AND ALGORITHM", "Rolin Jackson", Book::FANTASY,
                           Book::FICTION, "9780747532743", 70, 76.80, true),
                      target.id - 1);

        assert(bookQ->where(bookQ->ID, 1).title == "DATA STRUCTURE AND ALGORITHM");
        cout << "PASSED \n";

        cout << "TEST 2 : Delete Record ID 2 \t\t\t\t\t\t: ";
        auto target2 = bookQ->where(bookQ->ID, 2);
        bookQ->del(target2.id);
        assert(bookQ->head->size() == 8);
        cout << "PASSED \n";

        cout << "TEST 3 : Find Record 3 \t\t\t\t\t\t\t\t: ";
        auto target3 = bookQ->where(bookQ->ID, 3);
        assert(target3.id == 3);
        cout << "PASSED \n";

        cout << "TEST 4 : Duplicate Record 4 for finding purpose \t: ";
        auto result4 = bookQ->wheres(bookQ->CATEGORY, bookQ->where(bookQ->ID, 4).category);
        assert(result4->size() == 3);
        cout << "PASSED \n";
    }

private:
    BooksNode *searchByTitle(const string &title) const {
        struct BooksNode *result = nullptr;
        BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.title == title) {
                auto newNode = new BooksNode(current->book);
                if (result == nullptr) {
                    result = newNode;
                } else {
                    struct BooksNode *temp = result;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
            current = current->next; // move through list
        }
        return (result == nullptr || result->size() <= 0)
               ? throw ModalNotFoundException("Book with search query : title are not Found")
               : result;
    }

    BooksNode *searchByAuthor(const string &author) const {
        struct BooksNode *result = nullptr;
        BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.author == author) {
                auto newNode = new BooksNode(current->book);
                if (result == nullptr) {
                    result = newNode;
                } else {
                    struct BooksNode *temp = result;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
            current = current->next; // move through list
        }

        return (result == nullptr || result->size() <= 0)
               ? throw ModalNotFoundException("Book with search query : author are not Found")
               : result;
    }

    BooksNode *searchByCategory(enum Book::CATEGORY &category) const {
        BooksNode *result = nullptr;
        BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.category == category) {
                auto newNode = new BooksNode(current->book);
                if (result == nullptr) {
                    result = newNode;
                } else {
                    struct BooksNode *temp = result;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
            current = current->next; // move through list
        }

        return (result == nullptr || result->size() <= 0)
               ? throw ModalNotFoundException("Book with search query : CATEGORY are not Found")
               : result;
    }

    BooksNode *searchByGenre(enum Book::GENRE &genre) const {
        struct BooksNode *result = nullptr;
        BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.genre == genre) {
                auto newNode = new BooksNode(current->book);
                if (result == nullptr) {
                    result = newNode;
                } else {
                    struct BooksNode *temp = result;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
            current = current->next; // move through list
        }

        return (result == nullptr || result->size() <= 0)
               ? throw ModalNotFoundException("Book with search query : GENRE are not Found")
               : result;
    }

    Book searchByID(int id) const {
        BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.id == id) {
                return current->book;
            } else {
                current = current->next;
            }
        }

        throw ModalNotFoundException("Modal (Book) with search query of: id");
    }

    Book searchByIndex(int index) const {
        if (index < 0 || index >= head->size()) {
            throw ("Index out of bound. \n");
        }
        BooksNode *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;

        return current->book;
    }

    /**
     * https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
     * function to insert a current in a list. Note that this function expects a pointer to sorted as this can modify the head of the input linked list (similar to push())
     * @param sorted
     * @param current
     */
    static void insertForQuality(struct BooksNode **sorted, struct BooksNode *current) {
        /* Special case for the head end */
        if (*sorted == nullptr || (*sorted)->book.quantity >= current->book.quantity) {
            current->next = *sorted;
            *sorted = current;
        } else {
            /* Locate the BooksNode before the point of insertion */
            BooksNode *temp = *sorted;
            while (temp->next != nullptr && temp->next->book.quantity < current->book.quantity) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
};


#endif //ROSETTA_BOOK_STORE_BOOKQUERY_H
