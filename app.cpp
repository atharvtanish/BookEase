#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <conio.h>   

using namespace std;

class Book {
private:
    string isbn, title, author, edition, publication;

public:
    // Setters
    void setIsbn(string a) { isbn = a; }
    void setTitle(string b) { title = b; }
    void setAuthor(string c) { author = c; }
    void setEdition(string d) { edition = d; }
    void setPublication(string e) { publication = e; }

    // Getters with const
    string getIsbn() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getEdition() const { return edition; }
    string getPublication() const { return publication; }

    // Serialize book data to a file
    void save(ofstream& ofs) const {
        ofs << isbn << endl
            << title << endl
            << author << endl
            << edition << endl
            << publication << endl;
    }

    // Deserialize book data from a file
    void load(ifstream& ifs) {
        getline(ifs, isbn);
        getline(ifs, title);
        getline(ifs, author);
        getline(ifs, edition);
        getline(ifs, publication);
    }
};

// Function prototypes
void addBook(vector<Book>& books);
void deleteBook(vector<Book>& books);
void editBook(vector<Book>& books);
void searchBook(const vector<Book>& books);
void viewAllBooks(const vector<Book>& books);
void quit();
void loadBooks(vector<Book>& books);
void saveBooks(const vector<Book>& books);

int main() {
    vector<Book> books;
    loadBooks(books);

    string choice;
    while (true) {
        system("CLS");
        cout << "LIBRARY MANAGEMENT SYSTEM\n\n";
        cout << "[1] ADD BOOK\n";
        cout << "[2] DELETE BOOK\n";
        cout << "[3] EDIT BOOK\n";
        cout << "[4] SEARCH BOOK\n";
        cout << "[5] VIEW ALL BOOKS\n";
        cout << "[6] QUIT\n\n";
        cout << "ENTER CHOICE: ";
        getline(cin, choice);

        system("CLS");

        if (choice == "1") {
            addBook(books);
        } else if (choice == "2") {
            deleteBook(books);
        } else if (choice == "3") {
            editBook(books);
        } else if (choice == "4") {
            searchBook(books);
        } else if (choice == "5") {
            viewAllBooks(books);
        } else if (choice == "6") {
            quit();
            break;
        } else {
            cout << "INVALID CHOICE! Press any key to continue . . .";
            _getch();
        }
    }

    return 0;
}

void loadBooks(vector<Book>& books) {
    ifstream ifs("books.txt");
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            Book book;
            book.load(ifs);
            if (ifs.eof()) break;
            books.push_back(book);
        }
        ifs.close();
    }
}

void saveBooks(const vector<Book>& books) {
    ofstream ofs("books.txt");
    for (const Book& book : books) {
        book.save(ofs);
    }
    ofs.close();
}

void addBook(vector<Book>& books) {
    Book book;
    string isbn, title, author, edition, publication;
    cout << "Enter ISBN: ";
    getline(cin, isbn);
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Edition: ";
    getline(cin, edition);
    cout << "Enter Publication: ";
    getline(cin, publication);

    book.setIsbn(isbn);
    book.setTitle(title);
    book.setAuthor(author);
    book.setEdition(edition);
    book.setPublication(publication);

    books.push_back(book);
    saveBooks(books);

    cout << "BOOK ADDED SUCCESSFULLY!\n\nPress any key to continue . . .";
    _getch();
}

void deleteBook(vector<Book>& books) {
    string isbn;
    cout << "Enter ISBN of the book to delete: ";
    getline(cin, isbn);

    auto it = remove_if(books.begin(), books.end(), [&](const Book& book) {
        return book.getIsbn() == isbn;
    });

    if (it != books.end()) {
        books.erase(it, books.end());
        saveBooks(books);
        cout << "BOOK DELETED SUCCESSFULLY!\n\nPress any key to continue . . .";
    } else {
        cout << "BOOK NOT FOUND!\n\nPress any key to continue . . .";
    }
    _getch();
}

void editBook(vector<Book>& books) {
    string isbn;
    cout << "Enter ISBN of the book to edit: ";
    getline(cin, isbn);

    for (Book& book : books) {
        if (book.getIsbn() == isbn) {
            string title, author, edition, publication;
            cout << "Enter new Title: ";
            getline(cin, title);
            cout << "Enter new Author: ";
            getline(cin, author);
            cout << "Enter new Edition: ";
            getline(cin, edition);
            cout << "Enter new Publication: ";
            getline(cin, publication);

            book.setTitle(title);
            book.setAuthor(author);
            book.setEdition(edition);
            book.setPublication(publication);

            saveBooks(books);

            cout << "BOOK EDITED SUCCESSFULLY!\n\nPress any key to continue . . .";
            _getch();
            return;
        }
    }

    cout << "BOOK NOT FOUND!\n\nPress any key to continue . . .";
    _getch();
}

void searchBook(const vector<Book>& books) {
    string isbn;
    cout << "Enter ISBN: ";
    getline(cin, isbn);

    for (const Book& book : books) {
        if (book.getIsbn() == isbn) {
            cout << "ISBN: " << book.getIsbn() << endl;
            cout << "Title: " << book.getTitle() << endl;
            cout << "Author: " << book.getAuthor() << endl;
            cout << "Edition: " << book.getEdition() << endl;
            cout << "Publication: " << book.getPublication() << endl;
            cout << "\n\nPress any key to continue . . .";
            _getch();
            return;
        }
    }

    cout << "BOOK NOT FOUND!\n\nPress any key to continue . . .";
    _getch();
}

void viewAllBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "NO BOOKS AVAILABLE!\n\nPress any key to continue . . .";
        _getch();
        return;
    }

    for (const Book& book : books) {
        cout << "ISBN: " << book.getIsbn() << endl;
        cout << "Title: " << book.getTitle() << endl;
        cout << "Author: " << book.getAuthor() << endl;
        cout << "Edition: " << book.getEdition() << endl;
        cout << "Publication: " << book.getPublication() << endl << endl;
    }

    cout << "Press any key to continue . . .";
    _getch();
}

void quit() {
    exit(0);
}
