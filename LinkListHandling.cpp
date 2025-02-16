#include "LinkListHandling.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

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

// Function to read CSV and store articles in a linked list
Article* readCSV(const string& inputFile, int& count, bool trackIssues) {
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "(!) Error: Could not open " << inputFile << endl;
        return nullptr;
    }

    string line;
    Article* head = nullptr;
    Article* tail = nullptr;
    count = 0;
    int skipped = 0, recovered = 0;
    int rowNumber = 0, totalRows = 0;

    // Always skip first (header) row
    getline(file, line);

    while (getline(file, line)) {
        rowNumber++;
        totalRows++;
        
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
        if (fields[0].empty() || fields[1].empty() || fields[2].empty() || fields[3].empty()) {
            recovered++;
        }

        // Create new article node
        Article* newArticle = new Article{fields[0], fields[1], fields[2], fields[3], nullptr};

        // Insert into linked list
        if (!head) {
            head = newArticle;
            tail = newArticle;
        } else {
            tail->next = newArticle;
            tail = newArticle;
        }
        count++;
    }

    file.close();

    // cout << "(*) Successfully stored " << count << " articles from " << inputFile << endl;
    // cout << "Debug Info: Total Rows Read = " << totalRows << ", Stored = " << count << ", Skipped = " << skipped << ", Recovered = " << recovered << endl;
    
    return head;
}

// Function to display the first 'count' articles
void displayArticles(Article* head, int count) {
    Article* temp = head;
    int i = 0;
    while (temp && i < count) {
        std::cout << "Title: " << temp->title << "\n";
        std::cout << "Content: " << temp->content << "\n";
        std::cout << "Subject: " << temp->subject << "\n";
        std::cout << "Date: " << temp->date << "\n\n";
        temp = temp->next;
        i++;
    }
}


// Function to delete the entire linked list
void deleteList(Article*& head) {
    while (head) {
        Article* temp = head;
        head = head->next;
        delete temp;
    }
}

// Main function
// int main() {
//     int fakeCount = 0, trueCount = 0;

//     Article* fakeHead = readCSV("data-fake.csv", fakeCount, true); // Track issues only for data-fake.csv
//     Article* trueHead = readCSV("data-true.csv", trueCount, false);

//     cout << "\n\n(**) READ INTO LINKED LIST:" << endl;
//     cout << "(*) Successfully stored " << fakeCount << " articles from data-fake.csv" << endl;
//     cout << "(*) Successfully stored " << trueCount << " articles from data-true.csv" << endl;

//     return 0;
// }
