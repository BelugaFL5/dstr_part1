#include "HashSearch_Array.hpp"
#include <regex>
#include <iomanip>
#include <sstream>
#include <fstream>  // For file handling

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

// Tokenize content into words
void tokenizeText(const string& text, string words[], int& wordCount) {
    stringstream ss(text);
    string word;
    wordCount = 0;
    
    while (ss >> word && wordCount < MAX_WORDS) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        // Remove punctuation and special characters
        word.erase(remove_if(word.begin(), word.end(), 
                           [](char c) { return !isalnum(c); }), 
                  word.end());
        
        // Skip URLs and stop words
        if (word.empty() || word.find("http") == 0 || word.length() < 3 ||
            word == "the" || word == "and" || word == "for" || word == "that" ||
            word == "this" || word == "with" || word == "from" || word == "was" ||
            word == "are" || word == "has" || word == "have" || word == "had" ||
            word == "you" || word == "they" || word == "their") {
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
    HashTable hashTable;
    initializeHashTable(hashTable);
    int govArticles = 0;

    // Open file for writing output
    ofstream outputFile("output.txt");
    
    if (!outputFile.is_open()) {
        cout << "Error: Could not open output file for writing!" << endl;
        return;
    }
    
    outputFile << "\nAnalyzing government-related articles...\n";
    
    // Process articles
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
    
    // Get and store top words
    WordFreq topWords[MAX_WORDS];
    int topWordsCount = 0;
    getTopWords(hashTable, topWords, topWordsCount);
    
    outputFile << "\n(**) Found " << govArticles << " government-related articles\n";
    outputFile << "(**) Top " << min(TOP_WORDS, topWordsCount) << " words in fake government news:\n";
    
    for (int i = 0; i < min(TOP_WORDS, topWordsCount); i++) {
        outputFile << setw(20) << left << topWords[i].word 
                   << ": " << topWords[i].frequency << " occurrences\n";
    }
    
    // Close the file
    outputFile.close();
}