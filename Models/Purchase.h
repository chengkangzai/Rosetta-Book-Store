//
// Created by Cheng Kang Ching on 25/04/2021.
//

#ifndef ROSETTA_BOOK_STORE_PURCHASE_H
#define ROSETTA_BOOK_STORE_PURCHASE_H

// one purchase only type of Book
class Purchase {
public:
    enum CUSTOMER_TYPE {
        NORMAL_CUSTOMER, WHOLESALE, MEMBER
    };

    enum PAYMENT_TYPE {
        CASH, VISA_CARD, MASTER_CARD, E_WALLET, ONLINE_BANKING
    };

    int id;
    int quantity;
    double totalPrice;
    Book book;
    CUSTOMER_TYPE customerType;
    PAYMENT_TYPE paymentType;

    Purchase(
            int id,
            int quantity,
            Book book,
            CUSTOMER_TYPE customerType,
            PAYMENT_TYPE paymentType
    ) {
        this->id = id;
        this->quantity = quantity;
        this->totalPrice = customerType == WHOLESALE
                           ? (book.price * quantity) * 90 / 100
                           : customerType == MEMBER
                             ? (book.price * quantity) * 95 / 100
                             : book.price * quantity;
        this->book = book;
        this->customerType = customerType;
        this->paymentType = paymentType;
    }

    string toString() {
        return to_string(this->id) + ", " + to_string(this->quantity) + ", " + to_string(this->totalPrice) + ", " +
               this->getCustomerType(this->customerType) + ", " + this->getPaymentType(this->paymentType) + ", \n\t" +
               this->book.toString();
    }

    void print() {
        cout << this->toString() + "\n";
    }

    const char *getPaymentType(enum PAYMENT_TYPE paymentType) {
        switch (paymentType) {
            case CASH:
                return "CASH";
            case VISA_CARD:
                return "VISA_CARD";
            case MASTER_CARD:
                return "MASTER_CARD";
            case E_WALLET:
                return "E_WALLET";
            case ONLINE_BANKING:
                return "ONLINE_BANKING";
        }
    }

    const char *getCustomerType(enum CUSTOMER_TYPE customerType) {
        switch (customerType) {
            case NORMAL_CUSTOMER:
                return "NORMAL_CUSTOMER";
            case WHOLESALE:
                return "WHOLESALE";
            case MEMBER:
                return "MEMBER";
        }
    }


};

#endif //ROSETTA_BOOK_STORE_PURCHASE_H
