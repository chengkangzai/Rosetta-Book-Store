//
// Created by Cheng Kang Ching on 25/04/2021.
//

#ifndef ROSETTA_BOOK_STORE_PURCHASEQUERY_H
#define ROSETTA_BOOK_STORE_PURCHASEQUERY_H

#include <iostream>
#include <stack>
#include <cassert>

#include "../Models/Purchase.h"
#include "../Query/BookQuery.h"


class PurchaseQuery {
public:

    enum QUERY_TYPE {
        ID, BOOK_ID, PAYMENT_TYPE, CUSTOMER_TYPE
    };

    stack <Purchase> purchaseStack;

    PurchaseQuery *create(Purchase purchase) {
        this->purchaseStack.push(purchase);
        return this;
    }

    PurchaseQuery *printAll() {
        auto current = this->purchaseStack;

        while (!current.empty()) {
            current.top().print();
            current.pop();
        }
        return this;
    }

    PurchaseQuery *printReverse() {
        auto current = this->reverseThisStack();

        while (!current.empty()) {
            current.top().print();
            current.pop();
        }
        return this;
    }

    Purchase where(QUERY_TYPE queryType, int searchQuery) {
        if (queryType != ID)
            throw InvalidQueryType("This method only support ID");
        return this->findByID(searchQuery);
    }

    stack <Purchase> wheres(QUERY_TYPE queryType, int searchQuery) {
        if (queryType != BOOK_ID)
            throw InvalidQueryType("This method only support Book ID");
        return this->findByBookId(searchQuery);
    }

    stack <Purchase> wheres(QUERY_TYPE queryType, Purchase::PAYMENT_TYPE searchQuery) {
        if (queryType != PAYMENT_TYPE)
            throw InvalidQueryType("This method only support Payment Type");
        return this->findByPaymentType(searchQuery);
    }

    stack <Purchase> wheres(QUERY_TYPE queryType, Purchase::CUSTOMER_TYPE searchQuery) {
        if (queryType != CUSTOMER_TYPE)
            throw InvalidQueryType("This method only support Customer Type");
        return this->findByCustomerType(searchQuery);
    }


    /**
     * https://www.codespeedy.com/sorting-a-stack-using-stl-in-cpp/
     * @return
     */
    stack <Purchase> sortByTotalPrice() {
        stack <Purchase> current;

        while (!purchaseStack.empty()) {
            // pop out the first element
            Purchase temp = purchaseStack.top();
            purchaseStack.pop();

            while (!current.empty() && current.top().totalPrice > temp.totalPrice) {
                purchaseStack.push(current.top());
                current.pop();
            }

            // push temp in end
            current.push(temp);
        }
        return current;
    }

    PurchaseQuery *init() {
        auto books = BookQuery().init();
        this->create(
                Purchase(1, 1, books->where(books->ID, 1),
                         Purchase::NORMAL_CUSTOMER, Purchase::CASH)
        );
        this->create(
                Purchase(2, 200, books->where(books->ID, 2),
                         Purchase::WHOLESALE, Purchase::E_WALLET)
        );
        this->create(
                Purchase(3, 20, books->where(books->ID, 4),
                         Purchase::MEMBER, Purchase::ONLINE_BANKING)
        );
        this->create(
                Purchase(4, 5, books->where(books->ID, 4),
                         Purchase::MEMBER, Purchase::E_WALLET)
        );
        this->create(
                Purchase(5, 1, books->where(books->ID, 2),
                         Purchase::NORMAL_CUSTOMER, Purchase::CASH)
        );
        return this;
    }

    static void test() {
        cout << "TEST 1 : Creating test data \t\t\t\t\t\t: ";
        assert(PurchaseQuery().init()->purchaseStack.size() == 5);
        cout << "PASSED \n";

        cout << "TEST 2 : Get Record number 1 \t\t\t\t\t\t: ";
        assert(PurchaseQuery().init()->where(PurchaseQuery::ID, 1).id == 1);
        cout << "PASSED \n";

        cout << "TEST 3 : Get Multiple Record for Payment Type \t\t: ";
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::PAYMENT_TYPE, Purchase::CASH).size() == 2);
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::PAYMENT_TYPE, Purchase::E_WALLET).size() == 2);
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::PAYMENT_TYPE, Purchase::ONLINE_BANKING).size() == 1);
        cout << "PASSED \n";

        cout << "TEST 4 : Get Multiple Record for Customer Type \t\t: ";
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::NORMAL_CUSTOMER).size() == 2);
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::MEMBER).size() == 2);
        assert(PurchaseQuery().init()->wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::WHOLESALE).size() == 1);
        cout << "PASSED \n";
    }

private:
    /**
     * https://stackoverflow.com/questions/15648313/how-to-reverse-a-stack
     * @return
     */
    stack <Purchase> reverseThisStack() {
        stack <Purchase> tempStack;
        auto current = purchaseStack;

        while (!current.empty()) {
            auto item = current.top();
            current.pop();
            tempStack.push(item);
        }
        return tempStack;
    }

    Purchase findByID(int id) {
        stack <Purchase> tempStack;

        while (!purchaseStack.empty()) {
            if (purchaseStack.top().id == id)
                return purchaseStack.top();
            else
                purchaseStack.pop();
        }
        throw ModalNotFoundException("There is no modal found");
    }

    stack <Purchase> findByBookId(int id) {
        stack <Purchase> tempStack;

        while (!purchaseStack.empty()) {
            auto item = purchaseStack.top();
            if (item.book.id == id)
                tempStack.push(item);
            purchaseStack.pop();
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }

    stack <Purchase> findByPaymentType(Purchase::PAYMENT_TYPE paymentType) {
        stack <Purchase> tempStack;

        while (!purchaseStack.empty()) {
            auto item = purchaseStack.top();
            if (item.paymentType == paymentType)
                tempStack.push(item);
            purchaseStack.pop();
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }

    stack <Purchase> findByCustomerType(Purchase::CUSTOMER_TYPE customerType) {
        stack <Purchase> tempStack;

        while (!purchaseStack.empty()) {
            auto item = purchaseStack.top();
            if (item.customerType == customerType)
                tempStack.push(item);
            purchaseStack.pop();
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }
};


#endif //ROSETTA_BOOK_STORE_PURCHASEQUERY_H
