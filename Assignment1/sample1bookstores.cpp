#include <iostream>
#include <string>
#include <iomanip>

const int MAX_BOOKS = 100;

class Book {
public:
    int bookId;
    std::string bookName;
    std::string author;
    int yearPublished;
    std::string category;
    bool available;
    int quantity;

    Book() : bookId(0), yearPublished(0), available(false), quantity(0) {}
};

class Bookstore {
private:
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Bookstore() : bookCount(0) {}

    void addBook(const Book& book) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount] = book;
            bookCount++;
            std::cout << "Book added successfully!\n";
        } else {
            std::cout << "Maximum book limit reached. Cannot add more books.\n";
        }
    }

    void displayAllBooks() const {
        std::cout << "\nList of Books:\n";
        std::cout << std::setw(10) << "ID"
                  << std::setw(30) << "Title"
                  << std::setw(20) << "Author"
                  << std::setw(10) << "Year"
                  << std::setw(15) << "Category"
                  << std::setw(15) << "Available"
                  << std::setw(10) << "Quantity"
                  << "\n" << std::string(110, '-') << "\n";

        for (int i = 0; i < bookCount; ++i) {
            const auto& book = books[i];
            std::cout << std::setw(10) << book.bookId
                      << std::setw(30) << book.bookName
                      << std::setw(20) << book.author
                      << std::setw(10) << book.yearPublished
                      << std::setw(15) << (book.available ? "Yes" : "No")
                      << std::setw(10) << book.quantity << "\n";
        }
    }

    bool updateBook(int id, const Book& updatedBook) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].bookId == id) {
                books[i] = updatedBook;
                std::cout << "Book updated successfully!\n";
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
                std::cout << "Book deleted successfully!\n";
                return true;
            }
        }
        return false;
    }
};


void gatherBookDetails(Book& book) {
    char avail;

    std::cout << "Enter Book ID: ";
    std::cin >> book.bookId;
    std::cin.ignore();
    std::cout << "Enter Book Name: ";
    std::getline(std::cin, book.bookName);
    std::cout << "Enter Author: ";
    std::getline(std::cin, book.author);
    std::cout << "Enter Year Published: ";
    std::cin >> book.yearPublished;
    std::cin.ignore();
    std::cout << "Enter Category: ";
    std::getline(std::cin, book.category);
    std::cout << "Is the book available? (y/n): ";
    std::cin >> avail;
    std::cout << "Enter Quantity: ";
    std::cin >> book.quantity;

    book.available = (avail == 'y' || avail == 'Y');
}


void addBookDetails(Bookstore& store) {
    Book book;
    gatherBookDetails(book);

    char confirm;
    std::cout << "You are about to add the following book:\n"
              << "ID: " << book.bookId << "\nName: " << book.bookName
              << "\nAuthor: " << book.author << "\nYear: " << book.yearPublished
              << "\nCategory: " << book.category << "\nAvailable: "
              << (book.available ? "Yes" : "No") << "\n"
              << "Quantity: " << book.quantity << "\n"
              << "Confirm to add (y/n)? ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        store.addBook(book);
    } else {
        std::cout << "Book addition cancelled.\n";
    }
}


void updateBookDetails(Bookstore& store) {
    int id;
    std::cout << "Enter the Book ID to update: ";
    std::cin >> id;

    Book updatedBook;
    gatherBookDetails(updatedBook);
    if (store.updateBook(id, updatedBook)) {
        std::cout << "Book updated successfully!\n";
    } else {
        std::cout << "Book not found with ID: " << id << "\n";
