#include "char_search.hpp"
#include <regex>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include <string.h>

using namespace std;

// Check if the article is government-related
bool isGov(const string& subject) {
    return regex_search(subject, regex("government", regex_constants::icase));
}

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

// Function to insert a word using linear search (no hash table)
void insertWordLinearSearch(const string& word) {
    // Check if the word already exists in the wordList
    for (int i = 0; i < wordCount; i++) {
        if (wordList[i].word == word) {
            wordList[i].frequency++;
            return;  // Word found, increment frequency and return
        }
    }

    // If the word is not found, add it to the wordList
    if (wordCount < MAX_WORDS) {
        wordList[wordCount].word = word;
        wordList[wordCount].frequency = 1;
        wordCount++;
    }
}

// Function to write words and their frequencies to a file
void recordWords(const string& fileName, int govArticles, WordFreq wordList[]) {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        cout << "Error: Could not open output file for writing!" << endl;
        return;
    }

    // Write the total number of government-related articles
    outputFile << "Government-related articles: " << govArticles << endl << endl;

    // Write all words and their frequencies to the file
    for (int i = 0; i < wordCount; i++) {
        if (wordList[i].frequency > 0) {
            outputFile << setw(20) << left << wordList[i].word << wordList[i].frequency << " occurrences" << endl;
        }
    }

    // Close the file
    outputFile.close();
}

// Function to tokenize text and store valid words in an array
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
        insertWordLinearSearch(word);  // Insert the valid word into the word list
    }
}

// Sort for top words
void getTopWords(WordFreq result[], int& resultSize) {
    resultSize = 0;

    // Copy the wordList to result array
    for (int i = 0; i < wordCount; i++) {
        result[resultSize++] = wordList[i];
    }

    // Sort the result array by frequency (bubble sort)
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

    wordCount = 0;  // Reset word count

    int govArticles = 0;

    for (int i = 0; i < fakeSize; i++) {
        if (isGov(fakeArr[i].subject)) {
            govArticles++;
            string words[MAX_WORDS];
            int wordCount = 0;

            tokenizeText(fakeArr[i].content, words, wordCount);
        }
    }

    WordFreq topWords[MAX_WORDS];
    int topWordsCount = 0;
    getTopWords(topWords, topWordsCount);

    cout << "\n(**) Found " << govArticles << " government-related articles" << endl;
    cout << "(*) Top words: " << endl;
    for (int i = 0; i < min(TOP_WORDS, topWordsCount); i++) {
        cout << left << setw(6) << i + 1;
        cout << setw(15) << left << topWords[i].word << topWords[i].frequency << " occurrences" << endl;
    }

    // Call recordWords to store all words in a file
    recordWords("otherWords.txt", govArticles, wordList);

    // Calculate elapsed time
    double elapsedTime = calculateElapsedTime(start);
    cout << "\nTime taken for linear search: " << fixed << setprecision(1) << elapsedTime << "s" << endl;

    // Calculate memory usage in KB
    size_t memoryUsageKB = calcMemoryUsage(wordList);  // Calculate memory usage based on wordCount
    cout << "Memory usage: " << memoryUsageKB / 1024 << " KB" << endl;  // Convert to KB
}