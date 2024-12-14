#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_BOOKS = 100;

struct Book {
    int bookId;
    string bookName;
    string author;
    int yearPublished;
    string category;
    bool available;
    int quantity;

    Book() : bookId(0), yearPublished(0), available(false), quantity(0) {}
};

Book books[MAX_BOOKS];
int bookCount = 0;


void addBook(const Book& book) {
    if (bookCount < MAX_BOOKS) {
        books[bookCount] = book;
        bookCount++;
        cout << "Book added successfully!\n";
    } else {
        cout << "Maximum book limit reached. Cannot add more books.\n";
    }
}

void displayAllBooks() {
    cout << "\nList of Books:\n";
    cout << setw(10) << "ID"
         << setw(30) << "Title"
         << setw(20) << "Author"
         << setw(10) << "Year"
         << setw(15) << "Category"
         << setw(15) << "Available"
         << setw(10) << "Quantity"
         << "\n" << string(110, '-') << "\n";

    for (int i = 0; i < bookCount; ++i) {
        const auto& book = books[i];
        cout << setw(10) << book.bookId
             << setw(30) << book.bookName
             << setw(20) << book.author
             << setw(10) << book.yearPublished
             << setw(15) << (book.available ? "Yes" : "No")
             << setw(10) << book.quantity << "\n";
    }
}

bool updateBook(int id, const Book& updatedBook) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].bookId == id) {
            books[i] = updatedBook;
            cout << "Book updated successfully!\n";
            return true;
        }
    }
    return false;
}

bool deleteBook(int id) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].bookId == id) {

            for (int j = i; j < bookCount - 1; ++j) {
                books[j] = books[j + 1];
            }
            bookCount--;
            cout << "Book deleted successfully!\n";
            return true;
        }
    }
    return false;
}

void gatherBookDetails(Book& book) {
    char avail;

    cout << "Enter Book ID: ";
    cin >> book.bookId;
    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, book.bookName);
    cout << "Enter Author: ";
    getline(cin, book.author);
    cout << "Enter Year Published: ";
    cin >> book.yearPublished;
    cin.ignore();
    cout << "Enter Category: ";
    getline(cin, book.category);
    cout << "Is the book available? (y/n): ";
    cin >> avail;
    cout << "Enter Quantity: ";
    cin >> book.quantity;

    book.available = (avail == 'y' || avail == 'Y');
}

void addBookDetails() {
    Book book;
    gatherBookDetails(book);

    char confirm;
    cout << "You are about to add the following book:\n"
         << "ID: " << book.bookId << "\nName: " << book.bookName
         << "\nAuthor: " << book.author << "\nYear: " << book.yearPublished
         << "\nCategory: " << book.category << "\nAvailable: "
         << (book.available ? "Yes" : "No") << "\n"
         << "Quantity: " << book.quantity << "\n"
         << "Confirm to add (y/n)? ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        addBook(book);
    } else {
        cout << "Book addition cancelled.\n";
    }
}

void updateBookDetails() {
    int id;
    cout << "Enter the Book ID to update: ";
    cin >> id;

    Book updatedBook;
    gatherBookDetails(updatedBook);
    if (updateBook(id, updatedBook)) {
        cout << "Book updated successfully!\n";
    } else {
        cout << "Book not found with ID: " << id << "\n";
    }
}

void deleteBookDetails() {
    int id;
    cout << "Enter the Book ID to delete: ";
    cin >> id;
    if (deleteBook(id)) {
        cout << "Book deleted successfully!\n";
    } else {
        cout << "Book not found with ID: " << id << "\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "----- General Book Details -----\n";
        cout << "1. Add Book\n";
        cout << "2. Update Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Display All Books\n";
        cout << "0. Exit\n";
        cout << "-------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addBookDetails();
                break;
            case 2:
                updateBookDetails();
                break;
            case 3:
                deleteBookDetails();
                break;
            case 4:
                displayAllBooks();
                break;
            case 0:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
