#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Book {
public:
    string title, author, genre;
    int id, copies;

    void inputBook() {
        cout << "Enter Book ID: "; cin >> id;
        cin.ignore();
        cout << "Enter Title: "; getline(cin, title);
        cout << "Enter Author: "; getline(cin, author);
        cout << "Enter Genre: "; getline(cin, genre);
        cout << "Enter Copies Available: "; cin >> copies;
    }

    void displayBook() {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author << " | Genre: " << genre << " | Copies: " << copies << endl;
    }
};

class Library {
private:
    vector<Book> books;

    void saveToFile() {
        ofstream file("books.txt", ios::out);
        for (auto &b : books)
            file << b.id << " " << b.title << " " << b.author << " " << b.genre << " " << b.copies << "\n";
        file.close();
    }

    void loadFromFile() {
        ifstream file("books.txt");
        Book b;
        books.clear();
        while (file >> b.id) {
            file.ignore();
            getline(file, b.title, '\t');
            getline(file, b.author, '\t');
            getline(file, b.genre, '\t');
            file >> b.copies;
            books.push_back(b);
        }
        file.close();
    }

public:
    void addBook() {
        Book b;
        b.inputBook();
        books.push_back(b);
        saveToFile();
    }

    void displayBooks() {
        for (auto &b : books)
            b.displayBook();
    }

    void searchBook(string keyword) {
        for (auto &b : books)
            if (b.title.find(keyword) != string::npos || b.author.find(keyword) != string::npos || b.genre.find(keyword) != string::npos)
                b.displayBook();
    }

    void sortBooks() {
        sort(books.begin(), books.end(), [](Book a, Book b) { return a.title < b.title; });
    }
};

int main() {
    Library lib;
    int choice;
    string keyword;
    
    do {
        cout << "\nLibrary Management System";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search Book";
        cout << "\n4. Sort Books";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.displayBooks();
                break;
            case 3:
                cout << "Enter title/author/genre to search: ";
                cin.ignore();
                getline(cin, keyword);
                lib.searchBook(keyword);
                break;
            case 4:
                lib.sortBooks();
                break;
            case 5:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice!";
        }
    } while (choice != 5);

    return 0;
}
