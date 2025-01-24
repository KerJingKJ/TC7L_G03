// **************************************************************************
// Program: TC7L_G03_main2.cpp,
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC7L
// Tutorial Class: T13L
// Trimester: 2430
// Member_1: 243UC247BR | LIM PEI SHAN | LIM.PEI.SHAN@student.mmu.edu.my | 012-9811692
// Member_2: 243UC247D6 | CHAN KER JING | CHAN.KER.JING@student.mmu.edu.my | 011-59527593
// Member_3: 243UC247CB | TEOW YAN PING | TEOW.YAN.PING@student.mmu.edu.my | 019-4422688
// Member_4: 243UC247C1 | BERNICE GAN XINYI | BERNICE.GAN.XINYI@student.mmu.edu.my | 019-4100508
// **************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
using namespace std;

struct Book {
    int id;
    string name;
    string author;
    int year;
    string category;
    string status;
    int quantity;
    int pricing;
    string language;
    string location;
};

// Prototype declarations
void createTable(const string& line);
void selectFromTable(const string& line, vector<Book>& books);
void insertIntoTable(const string& line, vector<Book>& books);
void updateFromTable(const string& line, vector<Book>& books);
void deleteFromTable(const string& line, vector<Book>& books);


int main() {
    vector<Book> books; // Vector to store book details

    ifstream inputFile;
    ofstream outputFile;
    string filename;
    string line, fullCommand;

    cout << "Enter the filename: ";
    cin >> filename;

    inputFile.open(filename);

    if (inputFile) {
        if (inputFile.peek() == ifstream::traits_type::eof()) {
            cout << "The file is empty.\n";
        } else {
            while (getline(inputFile, line)) {
                fullCommand += line;
                if (line.find(';') != string::npos) {
                    if (fullCommand.find("CREATE TABLE") != string::npos) {
                        createTable(fullCommand);
                        outputFile.open("fileOutput3.csv");
                    }
                    else if (fullCommand.find("INSERT INTO") != string::npos) {
                        insertIntoTable(fullCommand, books);
                    }
                    else if (fullCommand.find("SELECT * FROM") != string::npos) {
                        selectFromTable(fullCommand, books);

                    }
                    else if (fullCommand.find("TABLES") != string::npos) //the others same also
                    {
                        cout << line << endl;
                        cout << "books" << endl;
                    }
                    else if (fullCommand.find("UPDATE") != string::npos) //the others same also
                    {
                        cout << endl;
                        cout << "Here will call a update function to update something to the list" << endl;
                        updateFromTable(fullCommand, books);
                    }
                    else if (fullCommand.find("DELETE FROM") != string::npos)
                    {
                        cout << endl;
                        deleteFromTable(fullCommand, books);
                    }
                    else if (fullCommand.find("SELECT COUNT") != string::npos)
                    {
                        cout << endl;
                        cout << "here is the count function" << endl;

                    }

                    fullCommand.clear();
                }
            }
            inputFile.close();
        }
    }
    else
    {
        cout << "Error opening the file.\n";
    }

    if (books.empty()) {
        cout << "No books available in the 'books' table to view in CSV format.\n";
    }
    else {
        cout << endl << "CSV file generated successfully." << endl;
        outputFile << "ID, Name, Author, Year, Category, Status, Quantity, Pricing, Language, Location" << endl;
        for (const auto& book : books) {

            outputFile << book.id << "," << book.name << "," << book.author << "," << book.year << ","
                      << book.category << "," << book.status << "," << book.quantity << "," << book.pricing << "," << book.language << "," << book.location << endl;

        }
        outputFile.close();
    }

    return 0;
}

void createTable(const string& line)
{
    cout << "Processing CREATE TABLE command...\n";
    cout << "Table structure initialized for storing book data.\n";
}

void selectFromTable(const string& line, vector<Book>& books)
{
   // cout << "Processing SELECT command...\n";
   for (const auto& book : books) {
    cout << book.id << "," << book.name << "," << book.author << "," << book.year << ","
                 << book.category << "," << book.status << "," << book.quantity << "," << book.pricing << "," << book.language << "," << book.location << endl;
   }
}

void insertIntoTable(const string& line, vector<Book>& books)
{
    regex pattern(R"(\((\d+),'([^']+)','([^']+)',(\d+),'([^']+)','([^']+)',(\d+),(\d+),'([^']+)','([^']+)'\))");
    smatch match;

    if (regex_search(line, match, pattern)) {
        Book book;
        book.id = stoi(match[1]);
        book.name = match[2];
        book.author = match[3];
        book.year = stoi(match[4]);
        book.category = match[5];
        book.status = match[6];
        book.quantity = stoi(match[7]);
        book.pricing = stoi(match[8]);
        book.language = match[9];
        book.location = match[10];

        books.push_back(book);
    }
    else
    {
        cout << "Error: Invalid INSERT INTO format.\n";
    }
}

void updateFromTable(const string& line, vector<Book>& books) {
    regex pattern(R"(UPDATE\s+books\s+SET\s+book_status\s*=\s*'([^']+)'\s+WHERE\s+book_id\s*=\s*(\d+);?)");
    smatch match;

    if (regex_search(line, match, pattern)) {
        string bookStatusToUpdate = match[1];
        int bookIdToUpdate = stoi(match[2]);
        bool found = false;
        for (auto& book : books){
            if (book.id == bookIdToUpdate) {
                book.status = bookStatusToUpdate;
                found = true;
                break;
            }
        }
        if (found)
        {
             cout << "Book with ID " << bookIdToUpdate << " updated successfully to '" << bookStatusToUpdate << "'.\n";
        }
        else{
            cout << "No book found with ID " << bookIdToUpdate << ".\n";
        }
    }
    else {
        cout << "Error: Invalid UPDATE format.\n";
    }
}

void deleteFromTable(const string& line, vector<Book>& books) {
    regex pattern(R"(DELETE FROM books\s+WHERE\s+book_id=(\d+);?)");
    smatch match;

    if (regex_search(line, match, pattern)) {
        int bookIdToDelete = stoi(match[1]);
        auto it = remove_if(books.begin(), books.end(), [bookIdToDelete](const Book& book) {
            return book.id == bookIdToDelete;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book with ID " << bookIdToDelete << " deleted successfully.\n";
        } else {
            cout << "No book found with ID " << bookIdToDelete << ".\n";
        }
    } else {
        cout << "Error: Invalid DELETE FROM format.\n";
    }
}

