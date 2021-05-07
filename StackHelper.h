//
// Created by Cheng Kang Ching on 07/05/2021.
//

#ifndef ROSETTA_BOOK_STORE_STACKHELPER_H
#define ROSETTA_BOOK_STORE_STACKHELPER_H

#include <iostream>
#include <stack>

using namespace std;

class StackHelper {
public:
    enum PRINT_METHOD {
        ASC, DESC
    };

    StackHelper *print(stack<Purchase> current, PRINT_METHOD printMethod) {
        if (printMethod == DESC) {
            stack<Purchase> temp = this->reverse(current);
            cout << "id" << setw(11)
                 << "Quantity" << setw(15)
                 << "Customer Type" << setw(20)
                 << "Payment Type" << setw(18)
                 << "Total Price" << setw(12)
                 << "Book Info" << setw(1)
                 << endl
                 << setfill('-') << setw(8 + 35 + 25 + 18 + 10 + 18 + 10 + 17) << "-" << endl
                 << setfill(' ');  //fill with spaces

            while (!temp.empty()) {
                auto purchase = temp.top();

                cout << setw(05) << left << purchase.id // left : Align in left
                     << setw(10) << left << purchase.quantity
                     << setw(21) << left << purchase.getCustomerType(purchase.customerType)
                     << setw(20) << left << purchase.getPaymentType(purchase.paymentType)
                     << setw(13) << left << purchase.totalPrice
                     << setw(01) << left << purchase.book.toString()
                     << endl;

                temp.pop();
            }
        } else {
            cout << "id" << setw(11)
                 << "Quantity" << setw(15)
                 << "Customer Type" << setw(20)
                 << "Payment Type" << setw(18)
                 << "Total Price" << setw(12)
                 << "Book Info" << setw(1)
                 << endl
                 << setfill('-') << setw(8 + 35 + 25 + 18 + 10 + 18 + 10 + 17) << "-" << endl
                 << setfill(' ');  //fill with spaces

            while (!current.empty()) {
                auto purchase = current.top();

                cout << setw(05) << left << purchase.id // left : Align in left
                     << setw(10) << left << purchase.quantity
                     << setw(21) << left << purchase.getCustomerType(purchase.customerType)
                     << setw(20) << left << purchase.getPaymentType(purchase.paymentType)
                     << setw(13) << left << purchase.totalPrice
                     << setw(01) << left << purchase.book.toString()
                     << endl;

                current.pop();
            }
        }
        return this;
    }

private:
    /**
     * https://stackoverflow.com/questions/15648313/how-to-reverse-a-stack
     * @return
     */
    stack<Purchase> reverse(stack<Purchase> current) {
        stack<Purchase> tempStack;

        while (!current.empty()) {
            auto item = current.top();
            tempStack.push(item);
            current.pop();
        }

        return tempStack;
    }

};


#endif //ROSETTA_BOOK_STORE_STACKHELPER_H
