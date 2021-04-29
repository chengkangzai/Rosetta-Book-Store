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

    Purchase() {

    }

    Purchase(
            int id,
            int quantity,
            Book book,
            CUSTOMER_TYPE customerType,
            PAYMENT_TYPE paymentType
    ) {
        this->id = id;
        this->quantity = quantity;
        this->book = book;
        this->customerType = customerType;
        this->paymentType = paymentType;
        this->totalPrice = this->customerType == WHOLESALE
                           ? (book.price * quantity) * 90 / 100
                           : this->customerType == MEMBER
                             ? (book.price * quantity) * 95 / 100
                             : book.price * quantity;
    }

    string toString() {
        return "[Purchase] id: " + to_string(this->id) +
               " | Qty: " + to_string(this->quantity) +
               " | Price: " + to_string(this->totalPrice) +
               " | Customer type: " + this->getCustomerType(this->customerType) +
               " | Payment type: " + this->getPaymentType(this->paymentType);
    }

    void print() {
        cout << this->toString() << endl << " \t";
        this->book.print();
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

    Purchase getFromCli() {
        cout << "Enter id" << endl;
        cin >> this->id;
        cin.ignore();
        fflush(stdout);

        int quantityTemp = 1;
        cout << "Enter Quantity" << endl;
        cin >> quantityTemp;
        this->quantity = quantityTemp;
        cin.ignore();
        fflush(stdout);

        bool isNotValidBook;
        do {
            int bookID;
            cout << "Enter Book ID" << endl;
            cin >> bookID;
            cin.ignore();
            fflush(stdout);
            try {
                this->book = BookQuery().where(BookQuery::ID, bookID);
                isNotValidBook = false;
            } catch (ModalNotFoundException modalNotFoundException) {
                cout << "The ID you enter do not have associated Book in our Data base " << endl;
                cout << "Please try again " << endl;
            }
        } while (isNotValidBook);


        cout << "Enter Customer Type " << endl
             << "1. NORMAL_CUSTOMER" << endl
             << "2. WHOLESALE" << endl
             << "3. MEMBER" << endl;
        int customerInput;
        cin >> customerInput;
        cin.ignore();
        fflush(stdout);
        switch (customerInput) {
            case 1 :
                this->customerType = Purchase::NORMAL_CUSTOMER;
                break;
            case 2 :
                this->customerType = Purchase::WHOLESALE;
                break;
            case 3 :
                this->customerType = Purchase::MEMBER;
                break;
            default:
                throw InvalidInput("Invalid Input");
        }

        cout << "Enter Payment Type " << endl
             << "1. CASH" << endl
             << "2. VISA_CARD" << endl
             << "3. MASTER_CARD" << endl
             << "4. E_WALLET" << endl
             << "5. ONLINE_BANKING" << endl;
        int paymentInput;
        cin >> paymentInput;
        cin.ignore();
        fflush(stdout);

        switch (paymentInput) {
            case 1:
                this->paymentType = Purchase::CASH;
                break;
            case 2:
                this->paymentType = Purchase::VISA_CARD;
                break;
            case 3:
                this->paymentType = Purchase::MASTER_CARD;
                break;
            case 4:
                this->paymentType = Purchase::E_WALLET;
                break;
            case 5:
                this->paymentType = Purchase::ONLINE_BANKING;
                break;
            default:
                throw InvalidInput("Invalid Input");
        }

        this->totalPrice = this->customerType == WHOLESALE
                           ? (book.price * quantity) * 90 / 100
                           : this->customerType == MEMBER
                             ? (book.price * quantity) * 95 / 100
                             : book.price * quantity;
        return *this;
    }


};

#endif //ROSETTA_BOOK_STORE_PURCHASE_H
