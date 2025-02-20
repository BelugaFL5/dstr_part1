#include "HashSearch_Array.hpp"
#include <regex>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include <string.h>

using namespace std;

// Hash function implementation to calculate the hash value for the word
unsigned int hashFunction(const string& word) {
    unsigned int hash = 0;
    for (char c : word) {
        hash = hash * 31 + c;  // Using 31 as multiplier for good distribution
    }
    return hash % HASH_TABLE_SIZE;  // Ensure the hash value fits within the table size
}

// Initialize the hash table, setting size to 0 and marking all slots as empty
void initializeHashTable(HashTable& hashTable) {
    hashTable.size = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable.table[i] = WordFreq();  // Initialize each slot with default values
    }
}

// Insert word into the hash table using linear probing for collision handling
void insertWord(HashTable& hashTable, const string& word) {
    if (hashTable.size >= HASH_TABLE_SIZE) return;  // Table is full
    
    unsigned int index = hashFunction(word);  // Compute the index for the word
    
    // Linear probing to handle collisions
    while (hashTable.table[index].isOccupied && 
           hashTable.table[index].word != word) {
        index = (index + 1) % HASH_TABLE_SIZE;  // Move to the next index in case of collision
    }
    
    if (!hashTable.table[index].isOccupied) {  // If the slot is empty, insert the word
        hashTable.table[index].word = word;
        hashTable.table[index].frequency = 1;
        hashTable.table[index].isOccupied = true;
        hashTable.size++;
    } else {  // If the word is already in the table, just increment the frequency
        hashTable.table[index].frequency++;
    }
}

// Check if the article's subject is related to government
bool isGov(const string& subject) {
    return regex_search(subject, regex("government", regex_constants::icase));  // Search for 'government' in the subject
}

// Function to write top words and their frequencies to a file, from startIdx to endIdx
void recordWords(const string& fileName, WordFreq wordList[], int startIdx, int endIdx) {
    ofstream outputFile(fileName);  // Open the file to write the results

    if (!outputFile.is_open()) {  // Check if the file was opened successfully
        cout << "Error: Could not open output file for writing!" << endl;
        return;
    }

    // Write the top words and their frequencies from the specified range (startIdx to endIdx)
    for (int i = startIdx; i < endIdx && i < MAX_WORDS; i++) {
        outputFile << setw(30) << left << wordList[i].word << wordList[i].frequency << " occurrences" << endl;
    }

    // Close the file after writing
    outputFile.close();
}

// Function to load stop words from a file and store them in an array
void loadStopWords(const string& fileName) {
    ifstream file(fileName);  // Open the stop words file
    string word;
    
    if (!file) {  // Check if the file is opened successfully
        cerr << "Error opening stop words file!" << endl;
        return;
    }

    // Read each word from the file and store it in the stopWords array
    while (file >> word && stopWordsCount < MAX_STOPWORDS) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert word to lowercase

        strncpy(stopWords[stopWordsCount], word.c_str(), MAX_WORD_LENGTH - 1);  // Store the word in the array
        stopWords[stopWordsCount][MAX_WORD_LENGTH - 1] = '\0';  // Ensure null-termination
        stopWordsCount++;
    }

    file.close();  // Close the file after reading
}

// Function to check if the given word is a stop word
bool isStopWord(const string& word) {
    for (int i = 0; i < stopWordsCount; i++) {  // Iterate through the stop words
        if (word == stopWords[i]) {  // If the word matches a stop word
            return true;  // Return true if it's a stop word
        }
    }
    return false;  // Return false if it's not a stop word
}

// Function to tokenize the given text into words, while applying necessary filters
void tokenizeText(const string& text, string words[], int& wordCount) {
    stringstream ss(text);  // Convert the text to a stringstream
    string word;
    wordCount = 0;  // Initialize word count

    while (ss >> word && wordCount < MAX_WORDS) {  // Read words until wordCount reaches the limit
        transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert word to lowercase

        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalnum(c); }), word.end());  // Remove punctuation and special characters

        // Skip stop words, words that are too short, URLs, and numbers
        if (word.empty() || word.find("http") == 0 || word.length() < 3 || isStopWord(word) || any_of(word.begin(), word.end(), ::isdigit)) {
            continue;
        }

        words[wordCount++] = word;  // Add valid words to the words array
    }
}

// Convert the hash table to a sorted array for top words based on frequency
void getTopWords(const HashTable& hashTable, WordFreq result[], int& resultSize) {
    resultSize = 0;

    // Copy non-empty entries from hash table to result array
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (hashTable.table[i].isOccupied) {
            result[resultSize++] = hashTable.table[i];  // Add word to result array
        }
    }
    
    // Sort the result array by frequency in descending order using bubble sort
    for (int i = 0; i < resultSize - 1; i++) {
        for (int j = 0; j < resultSize - i - 1; j++) {
            if (result[j].frequency < result[j + 1].frequency) {
                WordFreq temp = result[j];  // Swap elements to sort by frequency
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
}

// Main analysis function to process fake articles and extract top words
void analyzeContent_Array(Article fakeArr[], int fakeSize) {
    auto start = startTimer();  // Start time measurement

    // Load stop words from stopWords.txt
    loadStopWords("stopWords.txt");

    HashTable hashTable;  // Create a hash table to store word frequencies
    initializeHashTable(hashTable);
    int govArticles = 0;  // Initialize the count of government-related articles

    for (int i = 0; i < fakeSize; i++) {
        if (isGov(fakeArr[i].subject)) {  // Check if the article is government-related
            govArticles++;
            string words[MAX_WORDS];
            int wordCount = 0;

            // Tokenize the article's content into words
            tokenizeText(fakeArr[i].content, words, wordCount);

            // Insert each word into the hash table
            for (int j = 0; j < wordCount; j++) {
                insertWord(hashTable, words[j]);
            }
        }
    }

    WordFreq topWords[MAX_WORDS];  // Array to store the top words and their frequencies
    int topWordsCount = 0;
    getTopWords(hashTable, topWords, topWordsCount);  // Get top words from the hash table
    
    // Print the top government-related words and their frequencies
    cout << "\n(**) Found " << govArticles << " government-related articles" << endl;
    cout << "(*) Top words: " << endl;
    for (int i = 0; i < min(TOP_WORDS, topWordsCount); i++) {
        cout << left << setw(6) << i + 1;
        cout << setw(15) << left << topWords[i].word << topWords[i].frequency << " occurrences" << endl;
    }

    // Call recordWords to store all words in a file
    recordWords("nextTopWords.txt", topWords, TOP_WORDS, topWordsCount);

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "\nTime taken for hash search: " << fixed << setprecision(1) << elapsedTime << "s" << endl;

    // Calculate memory usage in KB
    size_t memoryUsage = calcMemoryUsage(hashTable);
    cout << "Memory usage: " << memoryUsage / (1024.0 * 1024.0) << "MB" << endl;
}
