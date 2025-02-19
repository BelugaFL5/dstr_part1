#ifndef HASHSEARCH_ARRAY_HPP
#define HASHSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>
#include <regex>

// Function declarations
unsigned int hashFunction(const std::string& word);
void initializeHashTable(HashTable& hashTable);
void insertWord(HashTable& hashTable, const std::string& word);
bool isGov(const std::string& subject);
void recordWords(const string& fileName, WordFreq wordList[], int startIdx, int endIdx);
void loadStopWords(const std::string& fileName);
bool isStopWord(const std::string& word);
void tokenizeText(const std::string& text, std::string words[], int& wordCount);
void getTopWords(const HashTable& hashTable, WordFreq result[], int& resultSize);
void analyzeContent_Array(Article fakeArr[], int fakeSize);
void merge(WordFreq arr[], int left, int mid, int right);

#endif // HASHSEARCH_ARRAY_HPP