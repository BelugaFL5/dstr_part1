#include "HashSearch_Array.hpp"
#include <regex>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include <string.h>

using namespace std;

// Hash function implementation
unsigned int hashFunction(const string& word) {
    unsigned int hash = 0;
    for (char c : word) {
        hash = hash * 31 + c;  // Using 31 as multiplier for good distribution
    }
    return hash % HASH_TABLE_SIZE;
}

// Initialize hash table
void initializeHashTable(HashTable& hashTable) {
    hashTable.size = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable.table[i] = WordFreq();
    }
}

// Insert word into hash table using linear probing
void insertWord(HashTable& hashTable, const string& word) {
    if (hashTable.size >= HASH_TABLE_SIZE) return;  // Table is full
    
    unsigned int index = hashFunction(word);
    
    // Linear probing to handle collisions
    while (hashTable.table[index].isOccupied && 
           hashTable.table[index].word != word) {
        index = (index + 1) % HASH_TABLE_SIZE;
    }
    
    if (!hashTable.table[index].isOccupied) {
        hashTable.table[index].word = word;
        hashTable.table[index].frequency = 1;
        hashTable.table[index].isOccupied = true;
        hashTable.size++;
    } else {
        hashTable.table[index].frequency++;
    }
}

// Check if the article is government-related
bool isGov(const string& subject) {
    return regex_search(subject, regex("government", regex_constants::icase));
}

// Function to write top words and their frequencies to a file
/* void recordWords(const string& fileName, int govArticles, const HashTable& hashTable) {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cout << "Error: Could not open output file for writing!" << endl;
        return;
    }

    // USE SORT METHOD

    // Write all words and their frequencies
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable.table[i].isOccupied) {
            outputFile << setw(20) << left << hashTable.table[i].word << hashTable.table[i].frequency << " occurrences\n";
        }
    }

    // Close the file
    outputFile.close();
} */

// Function to load stop words from a file
void loadStopWords(const string& fileName) {
    ifstream file(fileName);
    string word;
    
    if (!file) {
        cerr << "Error opening stop words file!" << endl;
        return;
    }

    // Read words from the file
    while (file >> word && stopWordsCount < MAX_STOPWORDS) {
        // Convert word to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Copy the word into the stopWords array
        strncpy(stopWords[stopWordsCount], word.c_str(), MAX_WORD_LENGTH - 1);
        stopWords[stopWordsCount][MAX_WORD_LENGTH - 1] = '\0';  // Ensure null-termination
        stopWordsCount++;
    }

    file.close();
}

// Function to check if the word is a stop word
bool isStopWord(const string& word) {
    for (int i = 0; i < stopWordsCount; i++) {
        if (word == stopWords[i]) {
            return true;  // Word is found in the stop words list
        }
    }
    return false;  // Word is not a stop word
}

// Go through text into words
void tokenizeText(const string& text, string words[], int& wordCount) {
    stringstream ss(text);
    string word;
    wordCount = 0;

    while (ss >> word && wordCount < MAX_WORDS) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert to lowercase

        // Remove punctuation and special characters
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalnum(c); }), word.end());

        // Skip stop words, words that are too short, URLs, and numbers
        if (word.empty() || word.find("http") == 0 || word.length() < 3 || isStopWord(word) || any_of(word.begin(), word.end(), ::isdigit)) {
            continue;
        }

        words[wordCount++] = word;
    }
}

// Convert hash table to sorted array for top words
void getTopWords(const HashTable& hashTable, WordFreq result[], int& resultSize) {
    resultSize = 0;
    
    // Copy non-empty entries to result array
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable.table[i].isOccupied) {
            result[resultSize++] = hashTable.table[i];
        }
    }
    
    // Sort using bubble sort
    for (int i = 0; i < resultSize - 1; i++) {
        for (int j = 0; j < resultSize - i - 1; j++) {
            if (result[j].frequency < result[j + 1].frequency) {
                WordFreq temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
}

// Main analysis function
void analyzeContent_Array(Article fakeArr[], int fakeSize) {
    auto start = startTimer(); // Start time measurement

    // Load stop words from stopWords.txt
    loadStopWords("stopWords.txt");

    HashTable hashTable;
    initializeHashTable(hashTable);
    int govArticles = 0;

    for (int i = 0; i < fakeSize; i++) {
        if (isGov(fakeArr[i].subject)) {
            govArticles++;
            string words[MAX_WORDS];
            int wordCount = 0;
            
            tokenizeText(fakeArr[i].content, words, wordCount);

            for (int j = 0; j < wordCount; j++) {
                insertWord(hashTable, words[j]);
            }
        }
    }

    WordFreq topWords[MAX_WORDS];
    int topWordsCount = 0;
    getTopWords(hashTable, topWords, topWordsCount);
    
    cout << "\n(**) Found " << govArticles << " government-related articles" << endl;
    cout << "(*) Top words: " << endl;
    for (int i = 0; i < min(TOP_WORDS, topWordsCount); i++) {
        cout << left << setw(6) << i + 1;
        cout << setw(15) << left << topWords[i].word << topWords[i].frequency << " occurrences" << endl;
    }

    // Call recordWords to store all words in a file
    // recordWords("otherWords.txt", govArticles, hashTable);

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "\nTime taken for hash search: " << fixed << setprecision(1) << elapsedTime << "s" << endl;

    // Calculate memory usage in KB
    size_t memoryUsageKB = calcMemoryUsage(hashTable);
    cout << "Memory usage: " << memoryUsageKB / 1024 << " KB" << endl;  // Convert to KB
}
