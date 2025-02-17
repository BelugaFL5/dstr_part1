#ifndef CHAR_SEARCH_HPP
#define CHAR_SEARCH_HPP

#include "char_handling.hpp"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

// Function declarations
bool isGov(const string& subject);
void loadStopWords(const string& fileName);
bool isStopWord(const string& word);
void insertWordLinearSearch(const string& word);
void recordWords(const string& fileName, int govArticles, WordFreq wordList[]);
void tokenizeText(const string& text, string words[], int& wordCount);
void getTopWords(WordFreq result[], int& resultSize);
void analyzeContent_Array(Article fakeArr[], int fakeSize);

#endif // CHAR_SEARCH_HPP