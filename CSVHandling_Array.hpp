#ifndef CSVHANDLING_ARRAY_HPP
#define CSVHANDLING_ARRAY_HPP

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

// Constants
const int MAX_STOPWORDS = 1000;        // Maximum number of stop words
const int MAX_WORD_LENGTH = 20;        // Maximum length of a stop word
const int HASH_TABLE_SIZE = 10007;     // A prime number to improve distribution
const int MAX_WORDS = 20000;          // Maximum unique words to track
const int TOP_WORDS = 100;            // Number of top words to display

// Stop words array and tracking variable
extern char stopWords[MAX_STOPWORDS][MAX_WORD_LENGTH];  // Array to hold stop words
extern int stopWordsCount;                             // To track the number of stop words loaded

// Structure to store article data
struct Article {
    string title, content, subject, date;
};

// Structure to store word frequency in hash table
struct WordFreq {
    string word;
    int frequency;
    bool isOccupied;  // Flag to track if slot is being used

    // Constructor to initialize members
    WordFreq() : word(""), frequency(0), isOccupied(false) {}
};

// Structure to store hash table with word frequencies
struct HashTable {
    WordFreq table[HASH_TABLE_SIZE];
    int size;  // Current number of elements

    // Constructor to initialize the hash table
    HashTable() : size(0) {}
};

// Function declarations
std::chrono::high_resolution_clock::time_point startTimer();
double calculateElapsedTime(std::chrono::high_resolution_clock::time_point start);
size_t calcMemoryUsage(int fakeSize, int trueSize);
size_t calcMemoryUsage(HashTable& hashTable);
string trim(string str);
void convertMonthToShortForm(string& date);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues);

#endif // CSVHANDLING_ARRAY_HPP
