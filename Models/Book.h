//
// Created by CCK on 2021-04-02.
//

#ifndef ROSETTA_BOOK_STORE_BOOK_H
#define ROSETTA_BOOK_STORE_BOOK_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Book {
public:
    enum CATEGORY {
        NON_FICTION, FICTION
    };

    enum GENRE {
        FANTASY, HISTORICAL, REALISTIC, SCIENCE, NARRATIVE, BIOGRAPHY, PERIODICALS, SELF_HELP, REFERENCE
    };

    int id{};
    string title{};
    string author{};
    GENRE genre{};
    CATEGORY category{};
    string ISBN{};
    int quantity{};
    double price{};
    bool isAvailable{};

    Book() {

    };

    Book(int id, string title, string author, enum GENRE genre, enum CATEGORY category, string ISBN, int quantity,
         double price, bool isAvailable) {
        this->id = id;
        this->title = std::move(title);
        this->author = std::move(author);
        this->genre = genre;
        this->category = category;
        this->ISBN = std::move(ISBN);
        this->quantity = quantity;
        this->price = price;
        this->isAvailable = isAvailable;
    }

    string toString() {
        return to_string(id) + ", " + title + ", " + author + ", " + this->getGenre(genre) + ", " +
               this->getCategory(category) + ", " + ISBN + ", " +
               to_string(quantity) + ", " + to_string(price) + ", " + to_string(isAvailable);
    }

    const char *getGenre(enum GENRE enumGenre) {
        switch (enumGenre) {
            case FANTASY:
                return "FANTASY";
            case HISTORICAL:
                return "HISTORICAL";
            case REALISTIC:
                return "REALISTIC";
            case SCIENCE:
                return "SCIENCE";
            case NARRATIVE:
                return "NARRATIVE";
            case BIOGRAPHY:
                return "BIOGRAPHY";
            case PERIODICALS:
                return "PERIODICALS";
            case SELF_HELP:
                return "SELF_HELP";
            case REFERENCE:
                return "REFERENCE";
        }
    }

    const char *getCategory(enum CATEGORY enumCategory) {
        switch (enumCategory) {
            case NON_FICTION:
                return "NON_FICTION";
            case FICTION:
                return "FICTION";
        }
    }

    void print() {
        cout << this->toString() << endl;
    }
};


#endif //ROSETTA_BOOK_STORE_BOOK_H
