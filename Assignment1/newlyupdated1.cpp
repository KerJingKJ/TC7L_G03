
  int book_quantity[MAX_BOOKS];
  int book_pricing[MAX_BOOKS];
  int book_count=0;

  if (book_count ==0) {
    cout <<"No books available in the 'books' table to view in CSV format.\n";
    return 0;
  }

  cout << "ID, Name, Author, Year, Category, Status, Quantity, Pricing" << endl;
  for (int i =0; i< book_count; i++){
    cout << book_id[i] << ","
        << book_name[i] << ","
        << book_author[i] << ","
        << book_year[i] << ","
        << book_category[i] << ","
        << book_status[i] << ","
        << book_quantity[i] << ","
        << book_pricing[i] << ",";

  }

  ifstream inputFile;
  string filename;
  string line; // Variable to store each line of the file

  // Get the filename from the user
  cout << "Enter the filename: ";
  cin >> filename;

  // Open the file
  inputFile.open(filename);

  // If the file successfully opened, process it
  if (inputFile)
  {
      // Check if the file is empty
      if (inputFile.peek() == ifstream::traits_type::eof())
      {
          cout << "The file is empty.\n";
      }
      else
      {
          // Read and display each line of the file
          while (getline(inputFile, line))
          {
              if (line.find("CREATE TABLE") != string::npos) {
                createTable(line);
              } else if (line.find("SELECT") != string::npos) {
                selectFromTable();
              } else {
                cout << line << endl;
              }
          }
      }
      // Close the file
      inputFile.close();
  }
  else
  {
      // Display an error message
      cout << "Error opening the file.\n";
  }

  return 0;

}

// Function definitions
void createTable(const string& line)   {      cout << "Processing CREATE TABLE command...\n";
      cout << "Table structure initialized for storing book data.\n"; //yea sure
  }

  void selectFromTable() {
    cout << "Processing SELECT command...\n";
  }
