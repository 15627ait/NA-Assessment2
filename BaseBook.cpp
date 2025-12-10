#include "BaseBook.h"

BaseBook::BaseBook(string n, string w, string c, bool s, string ad)
    : name(n), writer(w), code(c), status(s), addedOn(ad) {
}

BaseBook::~BaseBook() {
}

string BaseBook::getCode() const {
    return code;
}

string BaseBook::getName() const {
    return name;
}

bool BaseBook::isAvailable() const {
    return status;
}

void BaseBook::printDetails() const {
    cout << "Name: " << name << endl;
    cout << "Author: " << writer << endl;
    cout << "ISBN: " << code << endl;
    cout << "Available: " << (status ? "Yes" : "No") << endl;
    cout << "Added: " << addedOn << endl;
}

void BaseBook::borrowCopy() {
    if (status) {
        status = false;
        cout << "You have borrowed: " << name << endl;
    } else {
        cout << "Book is not available: " << name << endl;
    }
}

void BaseBook::returnCopy() {
    if (!status) {
        status = true;
        cout << "Book has been returned: " << name << endl;
    } else {
        cout << "This book was already marked as available." << endl;
    }
}

ShelfBook::ShelfBook(string n, string w, string c, bool s, string ad, string shelf)
    : BaseBook(n, w, c, s, ad), shelfCode(shelf) {
}

void ShelfBook::printDetails() const {
    BaseBook::printDetails();
    cout << "Shelf Code: " << shelfCode << endl;
}

OnlineBook::OnlineBook(string n, string w, string c, bool s, string ad, string lic)
    : BaseBook(n, w, c, s, ad), licenseEnd(lic) {
}

void OnlineBook::printDetails() const {
    BaseBook::printDetails();
    cout << "License End: " << licenseEnd << endl;
}

void sortAscending(vector<BaseBook*>& books) {
    for (size_t i = 0; i + 1 < books.size(); ++i) {
        for (size_t j = 0; j + 1 < books.size() - i; ++j) {
            if (books[j]->getName() > books[j + 1]->getName()) {
                BaseBook* tmp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = tmp;
            }
        }
    }
}

void sortDescending(vector<BaseBook*>& books) {
    for (size_t i = 0; i + 1 < books.size(); ++i) {
        for (size_t j = 0; j + 1 < books.size() - i; ++j) {
            if (books[j]->getName() < books[j + 1]->getName()) {
                BaseBook* tmp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = tmp;
            }
        }
    }
}

void sortMixed(vector<BaseBook*>& books) {
    if (books.size() < 3) return;
    BaseBook* tmp = books[0];
    books[0] = books[2];
    books[2] = tmp;
}

LibraryApp::~LibraryApp() {
    for (BaseBook* b : bookList) {
        delete b;
    }
}

void LibraryApp::addBook(BaseBook* b) {
    bookList.push_back(b);
}

BaseBook* LibraryApp::findBook(const string& code) {
    for (BaseBook* b : bookList) {
        if (b->getCode() == code) {
            return b;
        }
    }
    return nullptr;
}

void LibraryApp::showAllBooks() {
    cout << "\n--- Full book list ---" << endl;
    if (bookList.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    for (BaseBook* b : bookList) {
        b->printDetails();
        cout << "----------------------" << endl;
    }
}

void LibraryApp::showAvailableBooks() {
    cout << "\n--- Available books only ---" << endl;
    bool any = false;
    for (BaseBook* b : bookList) {
        if (b->isAvailable()) {
            any = true;
            b->printDetails();
            cout << "----------------------" << endl;
        }
    }
    if (!any) {
        cout << "No books are available right now." << endl;
    }
}

void LibraryApp::sortMenu() {
    while (true) {
        cout << "\n=== Sort Menu ===" << endl;
        cout << "1 - Sort to Ascending order (A to Z by name)" << endl;
        cout << "2 - Sort to Descending order (Z to A by name)" << endl;
        cout << "3 - Put in Mixed order (test case)" << endl;
        cout << "0 - Back to main menu" << endl;
        cout << "Choose: ";
        string opt;
        getline(cin, opt);

        if (opt == "0") {
            cout << "Returning to main menu..." << endl;
            break;
        } else if (opt == "1") {
            sortAscending(bookList);
            cout << "Books sorted in ascending order by name." << endl;
            showAllBooks();
        } else if (opt == "2") {
            sortDescending(bookList);
            cout << "Books sorted in descending order by name." << endl;
            showAllBooks();
        } else if (opt == "3") {
            sortMixed(bookList);
            cout << "Books changed to a mixed order." << endl;
            showAllBooks();
        } else {
            cout << "Wrong option in sort menu." << endl;
        }
    }
}
