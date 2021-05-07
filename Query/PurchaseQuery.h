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
#include "../StackHelper.h"

class PurchaseQuery {
public:

    enum QUERY_TYPE {
        ID, BOOK_ID, PAYMENT_TYPE, CUSTOMER_TYPE
    };

    stack<Purchase> purchaseStack;

    PurchaseQuery *create(Purchase purchase) {
        this->purchaseStack.push(purchase);
        return this;
    }

    /**
     * Print Purchase descending
     * @return
     */
    PurchaseQuery *printDesc() {
        if (this->purchaseStack.empty())
            cout << "There is not purchase in the systemp yet, please add one first :)" << endl;
        StackHelper().print(this->purchaseStack, StackHelper::DESC);
        return this;
    }

    /**
     * Print Purchase ascending
     * @return
     */
    PurchaseQuery *printAcs() {
        if (this->purchaseStack.empty())
            cout << "There is not purchase in the systemp yet, please add one first :)" << endl;
        StackHelper().print(this->purchaseStack, StackHelper::ASC);
        return this;
    }

    Purchase where(QUERY_TYPE queryType, int searchQuery) {
        if (queryType != ID)
            throw InvalidQueryType("This method only support ID");
        return this->findByID(searchQuery);
    }

    stack<Purchase> wheres(QUERY_TYPE queryType, int searchQuery) {
        if (queryType != BOOK_ID)
            throw InvalidQueryType("This method only support Book ID");
        return this->findByBookId(searchQuery);
    }

    stack<Purchase> wheres(QUERY_TYPE queryType, Purchase::PAYMENT_TYPE searchQuery) {
        if (queryType != PAYMENT_TYPE)
            throw InvalidQueryType("This method only support Payment Type");
        return this->findByPaymentType(searchQuery);
    }

    stack<Purchase> wheres(QUERY_TYPE queryType, Purchase::CUSTOMER_TYPE searchQuery) {
        if (queryType != CUSTOMER_TYPE)
            throw InvalidQueryType("This method only support Customer Type");
        return this->findByCustomerType(searchQuery);
    }


    /**
     * https://www.codespeedy.com/sorting-a-stack-using-stl-in-cpp/
     * @return
     */
    stack<Purchase> sortByTotalPrice() {
        stack<Purchase> sorted;
        stack<Purchase> current = this->purchaseStack;

        while (!current.empty()) {
            // pop out the first element
            Purchase temp = current.top();
            current.pop();

            while (!sorted.empty() && sorted.top().totalPrice > temp.totalPrice) {
                current.push(sorted.top());
                sorted.pop();
            }
            // push temp in end
            sorted.push(temp);
        }

        return sorted;
    }

    PurchaseQuery init() {
        auto books = BookQuery().init();
        this->create(
                Purchase(1, 1, books.where(BookQuery::ID, 1),
                         Purchase::NORMAL_CUSTOMER, Purchase::CASH)
        );
        this->create(
                Purchase(2, 200, books.where(BookQuery::ID, 2),
                         Purchase::WHOLESALE, Purchase::E_WALLET)
        );
        this->create(
                Purchase(3, 20, books.where(BookQuery::ID, 4),
                         Purchase::MEMBER, Purchase::ONLINE_BANKING)
        );
        this->create(
                Purchase(4, 5, books.where(BookQuery::ID, 4),
                         Purchase::MEMBER, Purchase::E_WALLET)
        );
        this->create(
                Purchase(5, 1, books.where(BookQuery::ID, 2),
                         Purchase::NORMAL_CUSTOMER, Purchase::CASH)
        );
        return *this;
    }

    static void test() {
        cout << "TEST 1 : Creating test data \t\t\t\t\t\t: ";
        assert(PurchaseQuery().init().purchaseStack.size() == 5);
        cout << "PASSED " << endl;

        cout << "TEST 2 : Get Record number 1 \t\t\t\t\t\t: ";
        assert(PurchaseQuery().init().where(PurchaseQuery::ID, 1).id == 1);
        cout << "PASSED " << endl;

        cout << "TEST 3 : Get Multiple Record for Customer Type \t\t: ";
        assert(PurchaseQuery().init().wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::NORMAL_CUSTOMER).size() == 2);
        assert(PurchaseQuery().init().wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::MEMBER).size() == 2);
        assert(PurchaseQuery().init().wheres(PurchaseQuery::CUSTOMER_TYPE, Purchase::WHOLESALE).size() == 1);
        cout << "PASSED " << endl;
    }

private:

    Purchase findByID(int id) {
        stack<Purchase> tempStack;
        auto current = this->purchaseStack;

        while (!current.empty()) {
            if (current.top().id == id)
                return current.top();
            else
                current.pop();
        }
        throw ModalNotFoundException("There is no modal found");
    }

    stack<Purchase> findByBookId(int id) {
        stack<Purchase> tempStack;
        auto current = this->purchaseStack;

        while (current.empty()) {
            auto item = current.top();
            if (item.book.id == id)
                tempStack.push(item);
            current.pop();
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }

    stack<Purchase> findByPaymentType(Purchase::PAYMENT_TYPE paymentType) {
        stack<Purchase> tempStack;
        auto current = this->purchaseStack;

        while (current.empty()) {
            auto item = current.top();
            if (item.paymentType == paymentType) {
                tempStack.push(item);
//                cout << "\n STUPID \n ";
            } else {
                cout << "\n STUPID \n ";
                current.pop();
            }
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }

    stack<Purchase> findByCustomerType(Purchase::CUSTOMER_TYPE customerType) {
        stack<Purchase> tempStack;
        stack<Purchase> current = this->purchaseStack;

        while (!current.empty()) {
            auto item = current.top();
            if (item.customerType == customerType)
                tempStack.push(item);
            current.pop();
        }

        if (tempStack.empty()) {
            throw ModalNotFoundException("There is no modal found");
        }

        return tempStack;
    }


};


#endif //ROSETTA_BOOK_STORE_PURCHASEQUERY_H
