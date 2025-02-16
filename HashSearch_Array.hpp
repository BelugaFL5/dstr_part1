#ifndef HASHSEARCH_ARRAY_HPP
#define HASHSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>
#include <regex>

unsigned int hashFunction(const string& word);
void initializeHashTable(HashTable& hashTable);
void insertWord(HashTable& hashTable, const string& word);
bool isGov(const string& subject);
void recordWords(const string& fileName, int govArticles, const HashTable& hashTable);
void tokenizeText(const string& text, string words[], int& wordCount);
void getTopWords(const HashTable& hashTable, WordFreq result[], int& resultSize);
void analyzeContent_Array(Article fakeArr[], int fakeSize);

#endif // HASHSEARCH_ARRAY_HPP