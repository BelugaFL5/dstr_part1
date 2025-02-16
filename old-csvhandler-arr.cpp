// this file isn't being run anywhere but still keep the code

/* #include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype> 

using namespace std;

struct Article {
    string title, content, subject, date;
};

// Function to trim spaces and special characters from strings
string trim(string str) {
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    
    // Remove any hidden or special characters
    str.erase(remove_if(str.begin(), str.end(), [](unsigned char c) {
        return !isprint(c);  // Keep only printable characters
    }), str.end());

    // Convert to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    
    return str;
}

// Function to correctly parse a CSV line (handles quoted fields with commas)
void parseCSVLine(const string& line, string fields[4]) {
    stringstream ss(line);
    string field;
    int fieldCount = 0;
    bool inQuotes = false;
    string tempField;

    while (ss.good() && fieldCount < 4) {
        char c = ss.get();
        if (c == '"') {
            inQuotes = !inQuotes;  // Toggle inside quote state
        } else if (c == ',' && !inQuotes) {
            fields[fieldCount++] = trim(tempField);
            tempField.clear();
        } else {
            tempField += c;
        }
    }

    if (!tempField.empty() || fieldCount < 4) {
        fields[fieldCount++] = trim(tempField);
    }

    while (fieldCount < 4) {
        fields[fieldCount++] = "Unknown";
    }
}

// Function to read CSV and store articles in an array
Article* readCSV(const string& inputFile, int& count, bool trackIssues = false) {
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "(!) Error: Could not open " << inputFile << endl;
        return nullptr;
    }

    string line;
    count = 0;
    int skipped = 0, recovered = 0;
    int rowNumber = 0, totalRows = 0;

    // Always skip first (header) row
    getline(file, line);

    // Determine the number of lines in the file (excluding header)
    while (getline(file, line)) {
        totalRows++;
    }

    // Reset file pointer after reading count
    file.clear();
    file.seekg(0);
    getline(file, line);  // Skip header again

    // Allocate memory for storing articles
    Article* articles = new Article[totalRows];

    while (getline(file, line)) {
        rowNumber++;
        
        // Remove hidden characters (Windows newline issues)
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());

        string fields[4];
        parseCSVLine(line, fields);

        trim(fields[0]);
        trim(fields[1]);
        trim(fields[2]);
        trim(fields[3]);

        // Count as recovered if at least one field was missing
        if (fields[0] == "" || fields[1] == "" || fields[2] == "" || fields[3] == "") {
            recovered++;
            if (trackIssues) {
                // COMMENTED OUT (FOR CLEAN TERMINAL)
                // cout << "(+) Recovered row " << rowNumber << ": " << fields[0] << " | " << fields[1] << " | " << fields[2] << " | " << fields[3] << endl;
            }
        }

        // Store article in the array
        articles[count] = {fields[0], fields[1], fields[2], fields[3]};
        count++;
    }

    file.close();

    cout << "(*) Successfully stored " << count << " articles from " << inputFile << endl;
    cout << "Debug Info: Total Rows Read = " << totalRows << ", Stored = " << count << ", Skipped = " << skipped << ", Recovered = " << recovered << endl;
    
    // DEBUG - Print the first article in the array
    if (count > 0) {
        cout << "\n\n[DEBUG] First article in array:" << endl;
        cout << "Article: " << articles[0].title << " | " << articles[0].content << " | " << articles[0].subject << " | " << articles[0].date << endl;
    }

    // DEBUG - Print the last article in the array
    if (count > 1) {
        cout << "\n\n[DEBUG] Last article in array:" << endl;
        cout << "Article: " << articles[count - 1].title << " | " << articles[count - 1].content << " | " << articles[count - 1].subject << " | " << articles[count - 1].date << endl;
    }

    return articles;
}

// Main function
int main() {
    int fakeCount = 0, trueCount = 0;

    // Read CSV and store in arrays
    Article* fakeArticles = readCSV("data-fake.csv", fakeCount, true); // Track issues only for data-fake.csv
    Article* trueArticles = readCSV("data-true.csv", trueCount, false);

    cout << "\n\n(**) FINAL RESULT:" << endl;
    cout << "(*) Successfully stored " << fakeCount << " articles from data-fake.csv" << endl;
    cout << "(*) Successfully stored " << trueCount << " articles from data-true.csv" << endl;

    // Free memory (since we used new[])
    delete[] fakeArticles;
    delete[] trueArticles;

    return 0;
}
 */