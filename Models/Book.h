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
    int id{};
    string title{};
    string author{};
    string genre{};
    string category{};
    string ISBN{};
    int quantity{};
    double price{};
    bool isAvailable{};

    Book(int id, string title, string author, string genre, string category, string ISBN, int quantity,
         double price, bool isAvailable) {
        this->id = id;
        this->title = std::move(title);
        this->author = std::move(author);
        this->genre = std::move(genre);
        this->category = std::move(category);
        this->ISBN = std::move(ISBN);
        this->quantity = quantity;
        this->price = price;
        this->isAvailable = isAvailable;
    }

    string toString() {
        return to_string(id) + ", " + title + ", " + author + ", " + genre + ", " + category + ", " + ISBN + ", " +
               to_string(quantity) + ", " + to_string(price) + ", " + to_string(isAvailable);
    }

    void print() {
        cout << this->toString() << endl;
    }
};


#endif //ROSETTA_BOOK_STORE_BOOK_H
