#include <iostream>
#include <string>
#include "BaseBook.h"
using namespace std;

int main() {
    LibraryApp app;

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
