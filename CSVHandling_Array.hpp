#ifndef CSVHANDLING_ARRAY_HPP
#define CSVHANDLING_ARRAY_HPP

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

// Constants
const int MAX_STOPWORDS = 1000;        // Maximum number of stop words
const int MAX_WORD_LENGTH = 20;        // Maximum length of a stop word
const int HASH_TABLE_SIZE = 15007;     // A prime number to improve distribution of hash values
const int MAX_WORDS = 20000;          // Maximum number of unique words to track
const int TOP_WORDS = 10;             // Number of top words to display

extern char stopWords[MAX_STOPWORDS][MAX_WORD_LENGTH];  // Array to store stop words
extern int stopWordsCount;                             // Variable to track the number of stop words loaded

// Structure to store article data
struct Article {
    string title, content, subject, date;
};

// Structure to store word frequency in hash table
struct WordFreq {
    string word;         // The word
    int frequency;       // Frequency of the word in the dataset
    bool isOccupied;     // Flag to track if a slot in the hash table is being used

    WordFreq() : word(""), frequency(0), isOccupied(false) {} // Constructor to initialize members
};

// Structure to store hash table with word frequencies
struct HashTable {
    WordFreq table[HASH_TABLE_SIZE];  // Array of WordFreq structures to hold the word data
    int size;  // Current number of elements in the hash table

    HashTable() : size(0) {} // Constructor to initialize the hash table
};

// Function declarations
void showLoadingIndicator();
std::chrono::high_resolution_clock::time_point startTimer();
double calcElapsedTime(std::chrono::high_resolution_clock::time_point start);
size_t calcMemoryUsage(int fakeSize, int trueSize);
size_t calcMemoryUsage(HashTable& hashTable);
string trim(string str);
void convertMonthToShortForm(string& date);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues);

#endif // CSVHANDLING_ARRAY_HPP