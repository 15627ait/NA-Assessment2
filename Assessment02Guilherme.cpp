#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class
class BaseBook {
protected:
    string name;
    string writer;
    string code;
    bool status;
    string addedOn;

public:
    BaseBook(string n, string w, string c, bool s, string ad)
        : name(n), writer(w), code(c), status(s), addedOn(ad) {
    }

    virtual ~BaseBook() {}

    string getCode() const { return code; }
    bool isAvailable() const { return status; }

    virtual void printDetails() const {
        cout << "Name: " << name << endl;
        cout << "Author: " << writer << endl;
        cout << "ISBN: " << code << endl;
        cout << "Available: " << (status ? "Yes" : "No") << endl;
        cout << "Added: " << addedOn << endl;
    }

    void borrowCopy() {
        if (status) {
            status = false;
            cout << "You have borrowed: " << name << endl;
        }
        else {
            cout << "Book not available: " << name << endl;
        }
    }

    void returnCopy() {
        status = true;
        cout << "Book returned: " << name << endl;
    }
};

// Physical book subclass
class ShelfBook : public BaseBook {
    string shelfCode;
public:
    ShelfBook(string n, string w, string c, bool s, string ad, string shelf)
        : BaseBook(n, w, c, s, ad), shelfCode(shelf) {
    }

    void printDetails() const override {
        BaseBook::printDetails();
        cout << "Shelf Code: " << shelfCode << endl;
    }
};

// Digital book subclass
class OnlineBook : public BaseBook {
    string licenseEnd;
public:
    OnlineBook(string n, string w, string c, bool s, string ad, string lic)
        : BaseBook(n, w, c, s, ad), licenseEnd(lic) {
    }

    void printDetails() const override {
        BaseBook::printDetails();
        cout << "License End: " << licenseEnd << endl;
    }
};

// Manager class
class LibraryApp {
    vector<BaseBook*> bookList;
public:
    ~LibraryApp() {
        for (BaseBook* b : bookList) delete b;
    }

    void addBook(BaseBook* b) { bookList.push_back(b); }

    BaseBook* findBook(const string& code) {
        for (BaseBook* b : bookList) {
            if (b->getCode() == code) return b;
        }
        return nullptr;
    }

    void showAvailableBooks() {
        cout << "\nAvailable Books:\n";
        for (BaseBook* b : bookList) {
            if (b->isAvailable()) {
                b->printDetails();
                cout << "----------------------\n";
            }
        }
    }
};

int main() {
    LibraryApp app;

    // Add books
    app.addBook(new ShelfBook("Awaken The Giant Within", "Tony Robbins", "9781471108211", true, "2025-11-01", "S1"));
    app.addBook(new ShelfBook("Unlimited Power", "Tony Robbins", "9780684845777", true, "2025-11-01", "S2"));
    app.addBook(new ShelfBook("Shoe Dog: A Memoir by the Creator of Nike", "Phil Knight", "9781471146725", true, "2025-11-01", "S3"));
    app.addBook(new OnlineBook("Playing the Game: The History of Adidas", "Rainer Karlsch", "9783791378782", true, "2025-11-01", "2027-01-01"));
    app.addBook(new OnlineBook("1001 Albums You Must Hear Before You Die", "Robert Dimery", "9780789320742", true, "2025-11-01", "2028-12-31"));

    cout << "--- Guilherme Library Console ---\n";

    while (true) {
        cout << "\nMenu:\n1 - Show available books\n2 - Borrow book\n3 - Return book\n0 - Exit\nSelect: ";
        string choice;
        getline(cin, choice);

        if (choice == "0") {
            cout << "Session ended.\n";
            break;
        }
        else if (choice == "1") {
            app.showAvailableBooks();
        }
        else if (choice == "2") {
            cout << "Type ISBN to borrow: ";
            string inp;
            getline(cin, inp);
            BaseBook* found = app.findBook(inp);
            if (found) {
                found->borrowCopy();
            }
            else {
                cout << "Not found.\n";
            }
        }
        else if (choice == "3") {
            cout << "Type ISBN to return: ";
            string inp;
            getline(cin, inp);
            BaseBook* found = app.findBook(inp);
            if (found) {
                found->returnCopy();
            }
            else {
                cout << "Not found.\n";
            }
        }
        else {
            cout << "Wrong option.\n";
        }
    }

    return 0;
}