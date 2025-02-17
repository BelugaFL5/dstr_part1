#ifndef CHAR_HANDLING_HPP
#define CHAR_HANDLING_HPP

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

// Constants
const int MAX_STOPWORDS = 1000;        // Maximum number of stop words
const int MAX_WORD_LENGTH = 20;        // Maximum length of a stop word
const int MAX_WORDS = 25000;          // Maximum unique words to track
const int TOP_WORDS = 50;            // Number of top words to display

// Structure to store article data
struct Article {
    string title, content, subject, date;
};

// Structure to store word frequency in hash table
struct WordFreq {
    string word;
    int frequency;

    // Constructor to initialize members
    WordFreq() : word(""), frequency(0) {}
};

// Stop words array and tracking variable
extern char stopWords[MAX_STOPWORDS][MAX_WORD_LENGTH];  // Array to hold stop words
extern int stopWordsCount;                             // To track the number of stop words loaded

// Array to store words and their frequencies
extern WordFreq wordList[MAX_WORDS];  // Array to store word frequencies
extern int wordCount;  // To track the number of unique words

// Function declarations
std::chrono::high_resolution_clock::time_point startTimer();
double calculateElapsedTime(std::chrono::high_resolution_clock::time_point start);
size_t calcMemoryUsage(int fakeSize, int trueSize);
size_t calcMemoryUsage(WordFreq wordList[]);
string trim(string str);
void convertMonthToShortForm(string& date);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues);

#endif // CHAR_HANDLING_HPP