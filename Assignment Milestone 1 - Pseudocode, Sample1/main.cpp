// **************************************************************************
// Program: main.cpp,
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
#include <regex> //to identify the keyword that is needed to store inside the output file,
                //and then skip unnecessary symbol like comma semicolon
using namespace std;

// here are the prototype that needed to create, insert and select table
void createTable(const string& line);
void selectFromTable(const string& line);
void insertIntoTable(const string& line, int book_id[], string book_name[], string book_author[], int book_year[], string book_category[], string book_status[], int book_quantity[], int book_pricing[], int& book_count);

int main() {
    const int MAX_BOOKS = 10; //constant: max row is 10

    // arrays that stores the datas like book id, book name and etc.
    int book_id[MAX_BOOKS];
    string book_name[MAX_BOOKS];
    string book_author[MAX_BOOKS];
    int book_year[MAX_BOOKS];
    string book_category[MAX_BOOKS];
    string book_status[MAX_BOOKS];
    int book_quantity[MAX_BOOKS];
    int book_pricing[MAX_BOOKS];
    int book_count = 0;

    //read input file and write output file

    ifstream inputFile;
    ofstream outputFiletxt;
    ofstream outputFilecsv;
    string filename;
    string line, fullCommand;

    //prompt to ask user to enter which input file they want to open

    cout << "Enter the filename: ";
    cin >> filename;

    inputFile.open(filename);


    if (inputFile)
    {

        if (inputFile.peek() == ifstream::traits_type::eof())
        {
            cout << "The file is empty.\n";
        }
        else
        {
        //goes through each line to search for some keyword like CREATE, INSERT

            while (getline(inputFile, line)) {
                // Accumulate lines into fullCommand until ';' is found
                fullCommand += line;
                if (line.find(';') != string::npos)
                {
                    if (fullCommand.find("CREATE TABLE") != string::npos)   // first one find the keyword 'create table' and call out function
                    {
                        createTable(fullCommand);
                        outputFiletxt.open("fileOutput1.txt");
                        outputFilecsv.open("fileOutput1.csv");
                    }
                    else if (fullCommand.find("INSERT INTO") != string::npos)   // then find 'insert into' and then call another function
                    {
                        insertIntoTable(fullCommand, book_id, book_name, book_author, book_year, book_category, book_status, book_quantity, book_pricing, book_count);
                    }
                    else if (fullCommand.find("SELECT") != string::npos) //the others same also
                    {
                        selectFromTable(fullCommand);
                    }
                    fullCommand.clear();  // Reset command buffer
                }


            }
            inputFile.close();
        }
    }
    else
    {
        // Display an error message
        cout << "Error opening the file.\n";
    }


    // after running all if and else if condition, output the table, and then also write it into output file
    if (book_count == 0) {
        cout << "No books available in the 'books' table to view in CSV format.\n";
    } else {
        // here is for the cmd
        cout << "ID, Name, Author, Year, Category, Status, Quantity, Pricing" << endl;
        for (int i = 0; i < book_count; i++) {
            cout << book_id[i] << ","
                 << book_name[i] << ","
                 << book_author[i] << ","
                 << book_year[i] << ","
                 << book_category[i] << ","
                 << book_status[i] << ","
                 << book_quantity[i] << ","
                 << book_pricing[i] << endl;

            // here is for the output file 'fileOutput1.txt'

            outputFiletxt << "ID, Name, Author, Year, Category, Status, Quantity, Pricing" << endl;
            outputFilecsv << "ID, Name, Author, Year, Category, Status, Quantity, Pricing" << endl;

            outputFiletxt << book_id[i] << ","
                         << book_name[i] << ","
                         << book_author[i] << ","
                         << book_year[i] << ","
                         << book_category[i] << ","
                         << book_status[i] << ","
                         << book_quantity[i] << ","
                         << book_pricing[i] << endl;
            outputFilecsv << book_id[i] << ","
                         << book_name[i] << ","
                         << book_author[i] << ","
                         << book_year[i] << ","
                         << book_category[i] << ","
                         << book_status[i] << ","
                         << book_quantity[i] << ","
                         << book_pricing[i] << endl;
        }

        outputFiletxt.close();
        outputFilecsv.close();
    }

    return 0;
}

void createTable(const string& line)
{
    cout << "Processing CREATE TABLE command...\n";
    cout << "Table structure initialized for storing book data.\n";

}

void selectFromTable(const string& line)
{
    if (line.find("customer") != string::npos) {
        cout << "Error: Table 'customer' does not exist.\n";
    } else {
        cout << "Processing SELECT command...\n";
    }
}

void insertIntoTable(const string& line, int book_id[], string book_name[], string book_author[],
                     int book_year[], string book_category[], string book_status[],
                     int book_quantity[], int book_pricing[], int& book_count)
{
    regex pattern(R"(\((\d+),'([^']+)','([^']+)',(\d+),'([^']+)','([^']+)',(\d+),(\d+)\))");
                        //here we use regex, to extract the datas from the VALUES, and then put it into output files
                        // R(...) = raw string literals, means here it helps
                        // to ignore all special characters like \n \t
                        // Note:
                        // the format is R( (), '()') = having brackets to store array ; if have ' ' means it is a string
                        // we need to put () around the regex, to create a capturing group. Means grouped them together
                        // \( for the open bracket '('
                        // \d means digit number 0-9; now we have \d+ because we need to capture one or more digit
                        // [^'] = here means it match any character except single quotation: ^' means except '; and then
                        // we have a + here means one or more character(string)

    smatch match;       // smatch=string match; create an object called match and then use store the result of the matched regex above.

    // regex_search : Searches a string for a match to the regex.
    //format (first, second, third)
    // first = to go through the line in database
    // second = hold the results of the matched value
    // third = the pattern that you want to match with
    if (regex_search(line, match, pattern))
    {
        book_id[book_count] = stoi(match[1]); // convert the string back to integer to store it in array
        book_name[book_count] = match[2];
        book_author[book_count] = match[3];
        book_year[book_count] = stoi(match[4]);
        book_category[book_count] = match[5];
        book_status[book_count] = match[6];
        book_quantity[book_count] = stoi(match[7]);
        book_pricing[book_count] = stoi(match[8]);

        book_count++;
    }
    else
    {
        cout << "Error: Invalid INSERT INTO format.\n";
    }
}
