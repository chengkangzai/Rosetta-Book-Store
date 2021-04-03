//
// Created by CCK on 2021-04-02.
//

#ifndef ROSETTA_BOOK_STORE_BOOKQUERY_H
#define ROSETTA_BOOK_STORE_BOOKQUERY_H

#include <iostream>
#include <utility>

#include "../Models/Book.h"
#include "../Exception/ModalNotFoundException.h"

using namespace std;

class BookQuery {
public:
    enum QUERY_TYPE {
        TITLE, ID, AUTHOR, INDEX
    };

    struct BooksNode {
        explicit BooksNode(Book book) : book(move(book)) {
        }

        Book book;
        struct BooksNode *next{};
    };

    struct BooksNode *head = nullptr;


    /**
     * @param TYPE Search type. Available query : TITLE,ID,AUTHOR,INDEX
     * @param searchQuery
     * @return
     */
    Book where(QUERY_TYPE TYPE, string searchQuery) {
        if (TYPE == TITLE)
            return this->searchByTitle(searchQuery);
        if (TYPE == ID)
            return this->searchByID(stoi(searchQuery));
        if (TYPE == AUTHOR)
            return this->searchByAuthor(searchQuery);
        if (TYPE == INDEX)
            return this->searchByIndex(stoi(searchQuery));

        throw exception("Invalid QUERY_TYPE !");
    }

    /**
     * @param TYPE Search type. Available query : ID,INDEX
     * @param searchQuery
     * @return
     */
    Book where(QUERY_TYPE TYPE, int searchQuery) {
        if (TYPE == ID)
            return this->searchByID(searchQuery);
        if (TYPE == INDEX)
            return this->searchByIndex(searchQuery);
        if (TYPE == AUTHOR || TYPE == TITLE) {
            throw exception("QUERY_TYPE not supported ! ps: Author and TITLE with int...?");
        }
        throw exception("Invalid QUERY_TYPE !");
    }

    BookQuery *create(Book book) {
        auto *newNode = new BooksNode(Book(move(book)));
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            return this;
        }

        BooksNode *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        return this;
    }


    const BookQuery *update(Book newBook, int index) const {
        if (index < 0 || index >= size()) {
            throw exception("Index out of bound. \n");
        }
        BooksNode *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->book = Book(newBook);
        return this;
    }

    /**
     * https://stackoverflow.com/questions/25599343/remove-an-element-from-a-linked-list-in-c/51127711
     * @param id that you wanted to delete!
     * @return
     */
    BookQuery *del(int id) {
        if (id < 0 || id >= size()) {
            throw exception("Index out of bound. \n");
        }

        if (id == 1) {
            head = head->next;
            return this;
        }

        BooksNode *prev = head; // empty header
        BooksNode *current = head->next; // the first valid node
        while (current != nullptr) {
            if (current->book.id == id) {
                break;
            } else {
                prev = current;
                current = current->next; // go to next value
            }
        }

        if (current == nullptr) { // if we reached end of list or the list is empty
            throw exception("Can't remove value: no match found.\n");
        } else {
//            cout << "Deleting: " << current << "\n";
            prev->next = current->next; // unlink the node you remove
            delete current; // delete the node
        }
    }

    BookQuery *printAll() {
        BooksNode *current = head;

        while (current != nullptr) {
            cout << current->book.toString() << "\n";
            current = current->next;
        }
        delete current;
        return this;
    }



    BookQuery *init() {
        this->create(
                Book(1, "HARRY POTTER", "J. K. ROWLING", "FANTASY", "FICTION",
                     "9780747532743", 50, 56.80, true));
        this->create(
                Book(2, "MEIN KAMPF", "ADOLF HITLER", "HISTORICAL", "FICTION",
                     "9780395925034", 5, 120.50, false));
        this->create(
                Book(3, "13 REASONS WHY", "JAY ASHER", "REALISTIC", "FICTION",
                     "9780451479327", 3, 63.2, true));
        this->create(
                Book(4, "THE INVISIBLE MAN", "H. G. WELLS", "SCIENCE", "FICTION",
                     "9781512091977", 5, 30.45, true));
        this->create(
                Book(5, "THE HUNGER GAMES", "SUZANNE COLLINS", "NARRATIVE", "NON-FICTION",
                     "9780439023481", 9, 124.41, true));
        this->create(
                Book(6, "I HAVE A DREAM", "MARTIN LUTHER KING JR.", "BIOGRAPHY", "NON-FICTION",
                     "9780375858871", 30, 100, true));
        this->create(
                Book(7, "CRIME AND PERIODICALS", "NOVA EVERLY", "PERIODICALS", "NON-FICTION",
                     "9781949202076", 2, 35.9, true));
        this->create(
                Book(8, "A NEW EARTH", "ECKHART TOLLE", "SELF-HELP", "NON-FICTION",
                     "9780452289963", 10, 15, true));
        this->create(
                Book(9, "THE HERO WITH A THOUSAND FACES", "JOSEPH CAMPBELL", "REFERENCE", "NON-FICTION",
                     "9781577315933", 6, 78, true));
        return this;
    }

private:
    int size() const {
        struct BooksNode *ptr = head;
        int temp = 0;

        while (ptr != nullptr) {
            temp++;
            ptr = ptr->next;
        }
        return temp;
    }

    void commit() {
        // TODO
    }

    Book searchByTitle(const string &title) const {
        struct BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.title == title) {
                return current->book;
            } else {
                current = current->next;
            }
        }

        throw ModalNotFoundException("Modal (Book) with search query of: title");
    }

    Book searchByAuthor(const string &author) const {
        struct BooksNode *current = head;

        while (current != nullptr) {
            if (current->book.author == author) {
                return current->book;
            } else {
                current = current->next;
            }
        }

        throw ModalNotFoundException("Modal (Book) with search query of: author");
    }

    Book searchByID(int id) const {
        struct BooksNode *current = head;

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
        if (index < 0 || index >= size()) {
            throw exception("Index out of bound. \n");
        }
        BooksNode *current = head;
        for (int i = 0; i < index; i++)
            current = current->next;

        return current->book;
    }
};


#endif //ROSETTA_BOOK_STORE_BOOKQUERY_H
