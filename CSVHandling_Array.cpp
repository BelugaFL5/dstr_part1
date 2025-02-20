#include "CSVHandling_Array.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

char stopWords[MAX_STOPWORDS][MAX_WORD_LENGTH];  // Array to hold stop words
int stopWordsCount = 0;  // Track the number of stop words loaded

// Start time measurement
std::chrono::high_resolution_clock::time_point startTimer() {
    return std::chrono::high_resolution_clock::now();
}

// Calculate elapsed time in seconds
double calcElapsedTime(std::chrono::high_resolution_clock::time_point start) {
    using namespace std::chrono;
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

// Function to calculate memory usage for articles
size_t calcMemoryUsage(int fakeSize, int trueSize) {
    // Approximate the size of the Article struct in bytes
    size_t articleSize = sizeof(Article); 
    size_t fakeMemory = fakeSize * articleSize;  // Memory used by fake articles
    size_t trueMemory = trueSize * articleSize;  // Memory used by true articles
    
    return fakeMemory + trueMemory;  // Total memory used by articles
}

// Function to calculate memory usage for the hash table
size_t calcMemoryUsage(HashTable& hashTable) {
    size_t memoryUsage = sizeof(hashTable);  // Base size of the hash table object

    // Add memory used by each WordFreq in the hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable.table[i].isOccupied) {
            memoryUsage += sizeof(hashTable.table[i]);  // Size of the WordFreq structure
            memoryUsage += hashTable.table[i].word.capacity();  // Memory used by the string inside WordFreq
        }
    }
    return memoryUsage;
}

// Function to calculate memory usage for storing articles
size_t calcMemoryUsage(Article* articles, int count) {
    size_t totalMemory = 0;

    // Memory used by the Article array itself
    totalMemory += count * sizeof(Article);  // Memory used by all Article structs

    // Memory used by the string fields in Article
    for (int i = 0; i < count; i++) {
        totalMemory += articles[i].title.capacity();    // Memory used by title string
        totalMemory += articles[i].content.capacity();  // Memory used by content string
        totalMemory += articles[i].subject.capacity();  // Memory used by subject string
        totalMemory += articles[i].date.capacity();     // Memory used by date string
    }

    return totalMemory;
}

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

// Function to convert full month names to short forms
void convertMonthToShortForm(string& date) {
    if (date.find("january") != string::npos) date.replace(date.find("january"), 7, "jan");
    else if (date.find("february") != string::npos) date.replace(date.find("february"), 8, "feb");
    else if (date.find("march") != string::npos) date.replace(date.find("march"), 5, "mar");
    else if (date.find("april") != string::npos) date.replace(date.find("april"), 5, "apr");
    else if (date.find("may") != string::npos) date.replace(date.find("may"), 3, "may");
    else if (date.find("june") != string::npos) date.replace(date.find("june"), 4, "jun");
    else if (date.find("july") != string::npos) date.replace(date.find("july"), 4, "jul");
    else if (date.find("august") != string::npos) date.replace(date.find("august"), 6, "aug");
    else if (date.find("september") != string::npos) date.replace(date.find("september"), 9, "sep");
    else if (date.find("october") != string::npos) date.replace(date.find("october"), 7, "oct");
    else if (date.find("november") != string::npos) date.replace(date.find("november"), 8, "nov");
    else if (date.find("december") != string::npos) date.replace(date.find("december"), 8, "dec");
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
        fields[fieldCount++] = "unknown";
    }

    convertMonthToShortForm(fields[3]); // Convert full month names to short form before storing
}

// Function to read CSV and store articles in an array
Article* readCSV(const string& inputFile, int& count, bool trackIssues = false) {
    auto start = startTimer();  // Start time measurement

    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "(!) Error: Could not open " << inputFile << endl;
        return nullptr;
    }

    string line;
    count = 0;
    int rowNumber = 0, totalRows = 0;

    // Skip first (header) row
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

        // Store article in the array
        articles[count] = {fields[0], fields[1], fields[2], fields[3]};
        count++;
    }

    file.close();
    cout << "\n(*) Successfully stored " << count << " articles from " << inputFile << " into array." << endl;

    // Display elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << fixed << setprecision(1);
    cout << "Time taken: " << elapsedTime << "s" << endl;

    // Display memory usage
    size_t memoryUsage = calcMemoryUsage(articles, count);
    cout << "Memory usage: " << memoryUsage / (1024.0 * 1024.0) << " MB" << endl;
    
    return articles;
}
