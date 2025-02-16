#ifndef HASHSEARCH_ARRAY_HPP
#define HASHSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>
#include <regex>

// Constants
const int HASH_TABLE_SIZE = 1000;
const int MAX_WORDS = 30000;  // Maximum unique words to track
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

unsigned int hashFunction(const string& word);
void initializeHashTable(HashTable& hashTable);
void insertWord(HashTable& hashTable, const string& word);
bool isGov(const string& subject);
void tokenizeText(const string& text, string words[], int& wordCount);
void getTopWords(const HashTable& hashTable, WordFreq result[], int& resultSize);
void analyzeContent_Array(Article fakeArr[], int fakeSize);

#endif // HASHSEARCH_ARRAY_HPP