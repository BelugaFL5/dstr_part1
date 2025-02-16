#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iomanip>
#include <chrono>
#include <map>
#include <vector>

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

// Function to convert full month names to short forms manually
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
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "(!) Error: Could not open " << inputFile << endl;
        return nullptr;
    }

    string line;
    count = 0;
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

        // Store article in the array
        articles[count] = {fields[0], fields[1], fields[2], fields[3]};
        count++;
    }

    file.close();
    cout << "(*) Successfully stored " << count << " articles from " << inputFile << endl;
    
    return articles;
}

// Function to extract the year from the article's date
int extractYear(string date) {
    date = trim(date);  // Ensure no leading/trailing spaces

    // Find last space (before year)
    size_t lastSpace = date.find_last_of(' ');
    if (lastSpace == string::npos) return 0; // Error case

    string yearStr = date.substr(lastSpace + 1); // Extract year

    try {
        return stoi(yearStr); // Convert to integer
    } catch (...) {
        return 0; // Handle errors
    }
}

// Heapify function to maintain heap property
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap sort function to sort the array
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to count the number of articles per year
void countArticlesByYear(Article* articles, int articleCount) {
    map<int, int> yearCount;

    // Count articles for each year
    for (int i = 0; i < articleCount; i++) {
        int year = extractYear(articles[i].date);
        if (year > 0) {
            yearCount[year]++;
        }
    }

    // Get the years and sort them using heap sort
    vector<int> years;
    for (const auto& entry : yearCount) {
        years.push_back(entry.first);
    }

    // Sort the years using heap sort
    heapSort(years);

    // Display the results sorted by year
    cout << "\n(**) Articles by Year:\n";
    for (int year : years) {
        cout << year << ": " << yearCount[year] << " articles" << endl;
    }
}

// Main function
int main() {
    int fakeCount = 0, trueCount = 0;

    // Read CSV and store in arrays
    Article* fakeArticles = readCSV("data-fake.csv", fakeCount, true);
    Article* trueArticles = readCSV("data-true.csv", trueCount, false);

    // Display article counts by year
    cout << "\n(**) Fake Articles by Year:\n";
    countArticlesByYear(fakeArticles, fakeCount);

    cout << "\n(**) True Articles by Year:\n";
    countArticlesByYear(trueArticles, trueCount);

    // Free memory
    delete[] fakeArticles;
    delete[] trueArticles;

    return 0;
}
