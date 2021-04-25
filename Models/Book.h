//
// Created by CCK on 2021-04-02.
//

#ifndef ROSETTA_BOOK_STORE_BOOK_H
#define ROSETTA_BOOK_STORE_BOOK_H

#include <iostream>
#include <string>
#include <sstream>
#include "../Exception/InvalidInput.h"

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

    Book getFromCli() {
        cout << "Enter Title" << endl;
        getline(cin, this->title, '\n');
        fflush(stdout);

        cout << "Enter id" << endl;
        cin >> this->id;
        cin.ignore();
        fflush(stdout);

        cout << "Enter Author" << endl;
        getline(cin, this->author, '\n');


        cout << "Pick a Genre" << endl
             << "1. FANTASY" << endl                        ß
             << "2. HISTORICAL" << endl
             << "3. REALISTIC" << endl
             << "4. SCIENCE" << endl
             << "5. NARRATIVE" << endl
             << "6. BIOGRAPHY" << endl
             << "7. PERIODICALS" << endl
             << "8. SELF_HELP" << endl
             << "9. REFERENCE" << endl;
        int genreTemp;
        cin >> genreTemp;
        switch (genreTemp) {
            case 1:
                this->genre = Book::FANTASY;
                break;
            case 2:
                this->genre = Book::HISTORICAL;
                break;
            case 3:
                this->genre = Book::REALISTIC;
                break;
            case 4:
                this->genre = Book::SCIENCE;
                break;
            case 5:
                this->genre = Book::NARRATIVE;
                break;
            case 6:
                this->genre = Book::BIOGRAPHY;
                break;
            case 7:
                this->genre = Book::PERIODICALS;
                break;
            case 8:
                this->genre = Book::SELF_HELP;
                break;
            case 9:
                this->genre = Book::REFERENCE;
                break;
            default:
                throw InvalidInput("Invalid Input");
        }

        cout << "Pick a Category" << endl
             << "1. NON_FICTION" << endl
             << "2. FICTION" << endl;
        int categoryTemp;
        cin >> categoryTemp;
        switch (categoryTemp) {
            case 1:
                this->category = Book::NON_FICTION;
                break;
            case 2:
                this->category = Book::FICTION;
                break;
            default:
                throw InvalidInput("Invalid Input");
        }

        cout << "Enter ISBN " << endl;
        cin >> this->ISBN;

        int quantityTemp = 1;
        cout << "Enter Quantity" << endl;
        cin >> quantityTemp;
        this->quantity = quantityTemp;

        cout << "Enter price" << endl;
        cin >> this->price;

        int availTemp;
        cout << "Available ? 1. Yes 2. No";
        cin >> availTemp;
        this->isAvailable = availTemp == 1;

        return *this;
    }
};


#endif //ROSETTA_BOOK_STORE_BOOK_H
