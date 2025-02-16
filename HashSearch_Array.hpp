#ifndef HASHSEARCH_ARRAY_HPP
#define HASHSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>
#include <regex>

// Constants for word frequency analysis
const int MAX_WORDS = 30000;  // Maximum unique words to track
const int TOP_WORDS = 200;    // Number of top words to display

// Structure to store word frequency
struct WordFreq {
    string word;
    int frequency;
};

bool isGov(const string& subject);
void tokenizeText(const string& text, string words[], int& wordCount);
void analyzeContent_Array(Article fakeArr[], int fakeSize);

#endif // HASHSEARCH_ARRAY_HPP