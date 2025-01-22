// **************************************************************************
// Program: TC7L_G03_main.cpp,
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
void createTable(const string& line, ofstream&);
void selectFromTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream&, ofstream&);
void insertIntoTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream&);
void deleteFromTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream&);

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
    ofstream outputTxtFile;
    string filename;
    string line, fullCommand;

    //prompt to ask user to enter which input file they want to open

    cout << "Enter the filename: ";
    cin >> filename;

    inputFile.open(filename);
    if (filename == "fileInput1.mdb")
    {
        outputCsvFile.open("fileOutput1.csv");
        outputTxtFile.open("fileOutput1.txt");
    }
    else
    {
        outputCsvFile.open("fileOutput2.csv");
        outputTxtFile.open("fileOutput2.txt");
    }


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
                if (fullCommand.find(';') != string::npos)
                {

                    if (fullCommand.find("CREATE") != string::npos)   // first one find the keyword 'create table'
                                                                      // and call out function
                    {
                        createTable(fullCommand, outputTxtFile);

                    }

                    else if (fullCommand.find ("DATABASES") != string::npos)
                    {
                        cout << "Here use the file system library to output the path" << endl; //Yan Ping's Part
                    }
                    else if (fullCommand.find("INSERT INTO") != string::npos)   // then find 'insert into'
                                                                                // and then call another function
                    {
                        insertIntoTable(fullCommand, customer_id, customer_name, customer_city, customer_state, customer_country,
                                        customer_phone, customer_email, customer_count, outputTxtFile);
                    }
                    else if (fullCommand.find("SELECT * FROM") != string::npos) //the others same also
                    {
                        selectFromTable(fullCommand, customer_id, customer_name, customer_city, customer_state, customer_country,
                                        customer_phone, customer_email, customer_count, outputTxtFile, outputCsvFile);
                    }
                    else if (fullCommand.find("TABLES") != string::npos) //the others same also
                    {
                        cout << ">" << line << endl;
                        cout << "customer" << endl;
                    }
                    else if (fullCommand.find("UPDATE") != string::npos) //the others same also
                    {
                        cout << "Here will call a update function to update something to the list" << endl;
                        // replace this with actual function
                    }
                    else if (fullCommand.find("DELETE FROM") != string::npos) {
                        deleteFromTable(fullCommand, customer_id, customer_name, customer_city, customer_state, customer_country,
                                        customer_phone, customer_email, customer_count, outputTxtFile);
                    }

                    else if (fullCommand.find("SELECT COUNT") != string::npos)
                    {
                        cout << "here is the count function" << endl;
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

    else{
        for (int i = 0; i < customer_count; i++) {
        outputCsvFile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email" << endl;
        outputCsvFile << customer_id[i] << ","
                    << customer_name[i] << ","
                    << customer_city[i] << ","
                    << customer_state[i] << ","
                    << customer_country[i] << ","
                    << customer_phone[i] << ","
                    << customer_email[i] << endl;
        }
    }

        outputCsvFile.close();
        outputTxtFile.close();
    //}

    return 0;
}

void createTable(const string& line, ofstream& outputfile)
{
    cout << ">" << line << endl;
    outputfile << ">" << line << endl;
}

void selectFromTable(const string& line,  vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream& outputtxtfile, ofstream& outputcsvfile)
{
    cout << ">" << line;
    cout << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email" << endl;
    outputtxtfile << ">" << line;
    outputtxtfile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email" << endl;
  //  outputcsvfile << "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email" << endl;
    for (int i = 0; i < customer_count; i++) {
            cout << customer_id[i] << ","
                    << customer_name[i] << ","
                    << customer_city[i] << ","
                    << customer_state[i] << ","
                    << customer_country[i] << ","
                    << customer_phone[i] << ","
                    << customer_email[i] << endl;
            outputtxtfile << customer_id[i] << ","
                    << customer_name[i] << ","
                    << customer_city[i] << ","
                    << customer_state[i] << ","
                    << customer_country[i] << ","
                    << customer_phone[i] << ","
                    << customer_email[i] << endl;
         /*   outputcsvfile << customer_id[i] << ","
                    << customer_name[i] << ","
                    << customer_city[i] << ","
                    << customer_state[i] << ","
                    << customer_country[i] << ","
                    << customer_phone[i] << ","
                    << customer_email[i] << endl; */


    }

}

void insertIntoTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream& outputfile)
{

    cout << ">" << line << endl;
    outputfile << ">" << line << endl;
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

void deleteFromTable(const string& line, vector<int>& customer_id, vector<string>& customer_name, vector<string>& customer_city,
                     vector<string>& customer_state, vector<string>& customer_country, vector<string>& customer_phone,
                     vector<string>& customer_email, int& customer_count, ofstream& outputfile) {
    cout << ">" << line;
    outputfile << ">" << line;
    cout << endl;
    outputfile << endl;
    regex pattern(R"(WHERE\s+customer_id\s*=\s*(\d+))");
    smatch match;

    if (regex_search(line, match, pattern)) {
        int idToDelete = stoi(match[1]);
        bool found = false;
        for (size_t i = 0; i < customer_id.size(); ++i) {
            if (customer_id[i] == idToDelete) {
                customer_id.erase(customer_id.begin() + i);
                customer_name.erase(customer_name.begin() + i);
                customer_city.erase(customer_city.begin() + i);
                customer_state.erase(customer_state.begin() + i);
                customer_country.erase(customer_country.begin() + i);
                customer_phone.erase(customer_phone.begin() + i);
                customer_email.erase(customer_email.begin() + i);
                customer_count--;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Error: Customer ID not found.\n";
        }
    } else {
        cout << "Error: Invalid DELETE FROM format.\n";
    }
}
