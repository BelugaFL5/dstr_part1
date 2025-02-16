#ifndef CSVHANDLING_ARRAY_HPP
#define CSVHANDLING_ARRAY_HPP

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

struct Article {
    string title, content, subject, date;
};

// Constants
const int HASH_TABLE_SIZE = 5000;
const int MAX_WORDS = 20000;  // Maximum unique words to track
const int TOP_WORDS = 200;    // Number of top words to display

// Structure to store word frequency
struct WordFreq {
    std::string word;
    int frequency;
    bool isOccupied;  // Flag to track if slot is being used

    // Constructor to initialize members
    WordFreq() {
        word = "";
        frequency = 0;
        isOccupied = false;
    }
};

// Structure to store hash table
struct HashTable {
    WordFreq table[HASH_TABLE_SIZE];
    int size;  // Current number of elements

    // Constructor
    HashTable() : size(0) {}
};

std::chrono::high_resolution_clock::time_point startTimer();
double calculateElapsedTime(std::chrono::high_resolution_clock::time_point start);
size_t calcMemoryUsage(int fakeSize, int trueSize);
size_t calcMemoryUsage(HashTable& hashTable);
string trim(string str);
void convertMonthToShortForm(string& date);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues);

#endif // CSVHANDLING_ARRAY_HPP
