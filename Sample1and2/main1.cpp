// **************************************************************************
// Program: main1.cpp,
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
#include <vector>
#include <regex> //to identify the keyword that is needed to store inside the output file,
                //and then skip unnecessary symbol like comma semicolon
using namespace std;

// here are the prototype that needed to create, insert and select table
void createTable(const string& line);
void selectFromTable(const string& line);
void insertIntoTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count);
int main(){

    // vactors that stores the datas like book id, book name and etc.
    vector <int> customer_id;
    vector <string> customer_name;
    vector <string> customer_city;
    vector <string> customer_state;
    vector <string> customer_country;
    vector <string> customer_phone;
    vector <string> customer_email;

    int customer_count = 0;

    //read input file and write output file

    ifstream inputFile;
    ofstream outputCsvFile;
    ofstream outputTxt1File;
    ofstream outputTxt2File;
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
                        if (filename == "fileInput1.mdb")
                        {
                            outputCsvFile.open("fileOutput1.csv");
                        }
                        else
                        {
                            outputCsvFile.open("fileOutput2.csv");
                        }

                    }
                    else if (fullCommand.find("INSERT INTO") != string::npos)   // then find 'insert into' and then call another function
                    {
                        insertIntoTable(fullCommand, customer_id, customer_name, customer_city, customer_state, customer_country, customer_phone, customer_email, customer_count);
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
    if (customer_count == 0)
    {
        cout << "No customer available in the 'customer' table to view in CSV format.\n";
    }
    else {
        // here is for the terminal and output file
        outputTxt1File.open("fileOutput1.txt");
        outputTxt2File.open("fileOutput2.txt");
        ifstream inputFile("fileInput1.mdb");
        while (getline(inputFile, line))
        {
            if (line.find("CREATE", 0) == 0 || line.find("DATABASES", 0) == 0 ||
            line.find("TABLES", 0) == 0 || line.find("INSERT", 0) == 0 ||
            line.find("SELECT", 0) == 0) {
            cout << "> " << line << endl;
            outputTxt1File << ">" << line << endl;
            outputTxt2File << ">" << line << endl;
            } else {
                cout << line << endl;
                outputTxt1File << line << endl;
                outputTxt2File << line << endl;
            }
        }
        inputFile.close();
        cout << "Customer ID, Customer Name, Customer City, Customer State, Customer Country, Customer Phone, Customer Email" << endl;
        outputTxt1File << "Customer ID, Customer Name, Customer City, Customer State, Customer Country, Customer Phone, Customer Email" << endl;
        outputTxt2File << "Customer ID, Customer Name, Customer City, Customer State, Customer Country, Customer Phone, Customer Email" << endl;
        outputCsvFile << "Customer ID, Customer Name, Customer City, Customer State, Customer Country, Customer Phone, Customer Email" << endl;
        for (int i = 0; i < customer_count; i++) {
            cout << customer_id[i] << ","
                    << customer_name[i] << ","
                    << customer_city[i] << ","
                    << customer_state[i] << ","
                    << customer_country[i] << ","
                    << customer_phone[i] << ","
                    << customer_email[i] << endl;

            // here is for the output file 'fileOutput1.txt'
            outputTxt1File << customer_id[i] << ","
                        << customer_name[i] << ","
                        << customer_city[i] << ","
                        << customer_state[i] << ","
                        << customer_country[i] << ","
                        << customer_phone[i] << ","
                        << customer_email[i] << endl;
            
            outputTxt2File << customer_id[i] << ","
                        << customer_name[i] << ","
                        << customer_city[i] << ","
                        << customer_state[i] << ","
                        << customer_country[i] << ","
                        << customer_phone[i] << ","
                        << customer_email[i] << endl;

            outputCsvFile << customer_id[i] << ","
                        << customer_name[i] << ","
                        << customer_city[i] << ","
                        << customer_state[i] << ","
                        << customer_country[i] << ","
                        << customer_phone[i] << ","
                        << customer_email[i] << endl;
        }



        outputCsvFile.close();
        outputTxt1File.close();
        outputTxt2File.close();
    }

    return 0;
}

void createTable(const string& line)
{
    cout << "Processing CREATE TABLE command...\n";
    cout << "Table structure initialized for storing customer data.\n";

}

void selectFromTable(const string& line)
{
    cout << "Processing SELECT command...\n";

}

void insertIntoTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count)
{
    regex pattern(R"(\(\s*(\d+)\s*,\s*'([^']+)'\s*,\s*'([^']+)'\s*,\s*'([^']+)'\s*,\s*'([^']+)'\s*,\s*'([^']+)'\s*,\s*'([^']+)'\s*\))");



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
                        // \s* used to catch whitespace

    smatch match;       // smatch=string match; create an object called match and then use store the result of the matched regex above.

    // regex_search : Searches a string for a match to the regex.
    //format (first, second, third)
    // first = to go through the line in database
    // second = hold the results of the matched value
    // third = the pattern that you want to match with
    if (regex_search(line, match, pattern))
    {
        customer_id.push_back(stoi(match[1])); // Convert the string back to integer to store in the vector
        customer_name.push_back(match[2]);     // use push back to add the id, name, etc dynamically to the vector
        customer_city.push_back(match[3]);
        customer_state.push_back(match[4]);
        customer_country.push_back(match[5]);
        customer_phone.push_back(match[6]);
        customer_email.push_back(match[7]);

        customer_count++;
    }
    else
    {
        cout << "Error: Invalid INSERT INTO format.\n" << line << endl;
    }
}