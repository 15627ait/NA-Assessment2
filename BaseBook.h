#ifndef BASEBOOK_H
#define BASEBOOK_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class BaseBook {
protected:
    string name;
    string writer;
    string code;
    bool status;
    string addedOn;

public:
    BaseBook(string n = "", string w = "", string c = "", bool s = true, string ad = "");
    virtual ~BaseBook();

    string getCode() const;
    string getName() const;
    bool isAvailable() const;

    virtual void printDetails() const;
    void borrowCopy();
    void returnCopy();
};

class ShelfBook : public BaseBook {
    string shelfCode;
public:
    ShelfBook(string n, string w, string c, bool s, string ad, string shelf);
    void printDetails() const override;
};

class OnlineBook : public BaseBook {
    string licenseEnd;
public:
    OnlineBook(string n, string w, string c, bool s, string ad, string lic);
    void printDetails() const override;
};

void sortAscending(std::vector<BaseBook*>& books);
void sortDescending(std::vector<BaseBook*>& books);
void sortMixed(std::vector<BaseBook*>& books);

class LibraryApp {
    std::vector<BaseBook*> bookList;

public:
    ~LibraryApp();

    void addBook(BaseBook* b);
    BaseBook* findBook(const std::string& code);
    void showAllBooks();
    void showAvailableBooks();
    void sortMenu();
};

#endif
