#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===== Base class =====
class BaseBook {
protected:
    string name;
    string writer;
    string code;
    bool status;
    string addedOn;

public:
    BaseBook(string n = "", string w = "", string c = "", bool s = true, string ad = "")
        : name(n), writer(w), code(c), status(s), addedOn(ad) {
    }

    virtual ~BaseBook() {}

    string getCode() const { return code; }
    string getName() const { return name; }
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
        } else {
            cout << "Book is not available: " << name << endl;
        }
    }

    void returnCopy() {
        if (!status) {
            status = true;
            cout << "Book has been returned: " << name << endl;
        } else {
            cout << "This book was already marked as available." << endl;
        }
    }
};

// ===== Shelf book =====
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

// ===== Online book =====
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

// ===== Sorting helpers (by name) =====
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

// Simple “mixed” order for testing
void sortMixed(vector<BaseBook*>& books) {
    if (books.size() < 3) return;
    BaseBook* tmp = books[0];
    books[0] = books[2];
    books[2] = tmp;
}

// ===== Manager class =====
class LibraryApp {
    vector<BaseBook*> bookList;

public:
    ~LibraryApp() {
        for (BaseBook* b : bookList) {
            delete b;
        }
    }

    void addBook(BaseBook* b) {
        bookList.push_back(b);
    }

    BaseBook* findBook(const string& code) {
        for (BaseBook* b : bookList) {
            if (b->getCode() == code) {
                return b;
            }
        }
        return nullptr;
    }

    void showAllBooks() {
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

    void showAvailableBooks() {
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

    void sortMenu() {
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
};

int main() {
    LibraryApp app;

    // Add books
    app.addBook(new ShelfBook("Awaken The Giant Within", "Tony Robbins",
        "9781471108211", true, "2025-11-01", "S1"));
    app.addBook(new ShelfBook("Unlimited Power", "Tony Robbins",
        "9780684845777", true, "2025-11-01", "S2"));
    app.addBook(new ShelfBook("Shoe Dog -  A Memoir by the Creator of Nike", "Phil Knight",
        "9781471146725", true, "2025-11-01", "S3"));
    app.addBook(new OnlineBook("Playing the Game: The History of Adidas", "Rainer Karlsch",
        "9783791378782", true, "2025-11-01", "2027-01-01"));
    app.addBook(new OnlineBook("1001 Albums You Must Hear Before You Die", "Robert Dimery",
        "9780789320742", true, "2025-11-01", "2028-12-31"));

    cout << "--- Guilherme Library Console (Test Version) ---" << endl;

    while (true) {
        cout << "\nMain Menu:" << endl;
        cout << "1 - Borrow a book" << endl;
        cout << "2 - Sort the order" << endl;
        cout << "3 - Show full list" << endl;
        cout << "4 - Return a book" << endl;
        cout << "5 - Exit" << endl;
        cout << "Select: ";
        string choice;
        getline(cin, choice);

        if (choice == "5") {
            cout << "Session ended." << endl;
            break;
        } else if (choice == "1") {
            cout << "Type ISBN to borrow: ";
            string inp;
            getline(cin, inp);
            BaseBook* found = app.findBook(inp);
            if (found) {
                found->borrowCopy();
            } else {
                cout << "Book not found." << endl;
            }
        } else if (choice == "2") {
            app.sortMenu();
        } else if (choice == "3") {
            app.showAllBooks();
        } else if (choice == "4") {
            cout << "Type ISBN to return: ";
            string inp;
            getline(cin, inp);
            BaseBook* found = app.findBook(inp);
            if (found) {
                found->returnCopy();
            } else {
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Wrong option." << endl;
        }
    }

    return 0;
}
