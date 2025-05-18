#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Book {
    char* title;
    char* author;
    char* isbn;
    double price;

    // Allocate memory and copy the content from src to dest
    void copyString(char*& dest, const char* src); // TODO: Implement deep copy of C-style string
    bool strEqual(const char* a, const char* b) const;

public:
    // TODO: Implement constructor to initialize book info using copyString
    Book(const char* t, const char* a, const char* i, double p);

    // TODO: Implement copy constructor for deep copy
    Book(const Book& other);

    // TODO: Implement destructor to free allocated memory
    ~Book();

    // TODO: Compare two books by their ISBN
    bool operator==(const Book& other) const;

    // Getter for ISBN
    const char* getISBN() const;

    // TODO: Print book information
    void printInfo() const;
};

void Book::copyString(char*& dest, const char* src) {
    int len = 0;
    while (src[len] != '\0') len++;
    dest = new char[len + 1];
    for (int i = 0; i <= len; ++i) dest[i] = src[i];
}

bool Book::strEqual(const char* a, const char* b) const {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == b[i];
}

Book::Book(const char* t, const char* a, const char* i, double p) : price(p) {
    copyString(title, t);
    copyString(author, a);
    copyString(isbn, i);
}

Book::Book(const Book& other) : price(other.price) {
    copyString(title, other.title);
    copyString(author, other.author);
    copyString(isbn, other.isbn);
}

Book::~Book() {
    delete[] title;
    delete[] author;
    delete[] isbn;
}

bool Book::operator==(const Book& other) const {
    return strEqual(isbn, other.isbn);
}

const char* Book::getISBN() const {
    return isbn;
}

void Book::printInfo() const {
    cout << "[" << title << "] by " << author << " (ISBN: " << isbn << ", Price: " << price << ")" << endl;
}


class Inventory {
    Book** books;
    int size;
    int capacity;

    // TODO: Double the array size and copy existing book pointers
    void resize();
    bool strEqual(const char* a, const char* b) const;

public:
    // TODO: Initialize empty inventory with given capacity
    Inventory(int cap = 10);

    // TODO: Free all dynamically allocated Book objects and array
    ~Inventory();

    // TODO: Add new book to inventory; throw error if duplicate ISBN
    void addBook(const Book& b);

    // TODO: Remove book by ISBN; throw error if not found
    void removeBook(const char* isbn);

    // TODO: Return pointer to book if found; else return nullptr
    Book* searchBook(const char* isbn);

    // TODO: Print all books in inventory
    void printAll() const;
};

bool Inventory::strEqual(const char* a, const char* b) const {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == b[i];
}

void Inventory::resize() {
    capacity *= 2;
    Book** newBooks = new Book * [capacity];
    for (int i = 0; i < size; ++i) {
        newBooks[i] = books[i];
    }
    delete[] books;
    books = newBooks;
}

Inventory::Inventory(int cap) : size(0), capacity(cap) {
    books = new Book * [capacity];
}

Inventory::~Inventory() {
    for (int i = 0; i < size; ++i) {
        delete books[i];
    }
    delete[] books;
}

void Inventory::addBook(const Book& b) {
    for (int i = 0; i < size; ++i) {
        if (*books[i] == b) {
            cout << "Error: Duplicate book!" << endl;
            return;
        }
    }
    if (size >= capacity) resize();
    books[size++] = new Book(b);
    cout << "Book Added!" << endl;
}

void Inventory::removeBook(const char* isbn) {
    for (int i = 0; i < size; ++i) {
        if (strEqual(books[i]->getISBN(), isbn)) {
            delete books[i];
            for (int j = i; j < size - 1; ++j) {
                books[j] = books[j + 1];
            }
            --size;
            cout << "Book Removed!" << endl;
            return;
        }
    }
    cout << "Error: Book not found!" << endl;
}

Book* Inventory::searchBook(const char* isbn) {
    for (int i = 0; i < size; ++i) {
        if (strEqual(books[i]->getISBN(), isbn))
            return books[i];
    }
    return nullptr;
}

void Inventory::printAll() const {
    cout << "Book List:" << endl;
    for (int i = 0; i < size; ++i) {
        books[i]->printInfo();
    }
}

int main() {
    Inventory inv;
    int choice;

    while (true) {
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            char t[100], a[100], i[100];
            double p;
            cout << "Enter title, author, isbn, price:\n";
            cin.getline(t, 100);
            cin.getline(a, 100);
            cin.getline(i, 100);
            cin >> p;
            cin.ignore();

            try {
                inv.addBook(Book(t, a, i, p));
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 2) {
            char i[100];
            cin.getline(i, 100);
            try {
                inv.removeBook(i);
            }
            catch (exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 3) {
            char i[100];
            cin.getline(i, 100);
            Book* b = inv.searchBook(i);
            if (b) b->printInfo();
            else cout << "Book not found!\n";
        }
        else if (choice == 4) {
            inv.printAll();
        }
        else if (choice == 5) {
            cout << "Program exit!" << endl;
            break;
        }
    }

    return 0;
}

