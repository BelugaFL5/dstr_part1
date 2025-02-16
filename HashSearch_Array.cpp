#include "HashSearch_Array.hpp"
#include <regex>
#include <iomanip>

using namespace std;

// Function to check if the article is government-related
bool isGov(const string& subject) {
    return regex_search(subject, regex("government", regex_constants::icase));
}

// Function to clean and tokenize text
void tokenizeText(const string& text, string words[], int& wordCount) {
    stringstream ss(text);
    string word;
    wordCount = 0;
    
    while (ss >> word && wordCount < MAX_WORDS) {
        // Convert to lowercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        // Remove punctuation and special characters
        word.erase(remove_if(word.begin(), word.end(), 
                           [](char c) { return !isalnum(c); }), 
                  word.end());
        
        // Skip empty strings and common stop words
        if (word.empty() || word == "the" || word == "a" || word == "an" || 
            word == "and" || word == "or" || word == "but" || word == "in" || 
            word == "on" || word == "at" || word == "to" || word == "for" || 
            word == "of" || word == "with" || word == "by" || word == "you" || 
            word == "i" || word == "he" || word == "she" || word == "it" ||
            word == "we" || word == "they" || word == "is" || word == "are" || 
            word == "is" || word == "that" || word == "this") {
            continue;
        }
        
        words[wordCount++] = word;
    }
}

// Function to analyze word frequencies in government-related fake news
void analyzeContent_Array(Article fakeArr[], int fakeSize) {
    WordFreq wordFreqs[MAX_WORDS] = {};  // Initialize array of WordFreq structures
    int uniqueWords = 0;
    
    // Process each fake article
    for (int i = 0; i < fakeSize; i++) {
        // Only process government-related articles
        if (isGov(fakeArr[i].subject)) {
            string words[MAX_WORDS];
            int wordCount = 0;
            
            // Tokenize the content
            tokenizeText(fakeArr[i].content, words, wordCount);
            
            // Count word frequencies
            for (int j = 0; j < wordCount; j++) {
                bool found = false;
                
                // Check if word already exists in frequency array
                for (int k = 0; k < uniqueWords; k++) {
                    if (wordFreqs[k].word == words[j]) {
                        wordFreqs[k].frequency++;
                        found = true;
                        break;
                    }
                }
                
                // Add new word if not found and there's space
                if (!found && uniqueWords < MAX_WORDS) {
                    wordFreqs[uniqueWords].word = words[j];
                    wordFreqs[uniqueWords].frequency = 1;
                    uniqueWords++;
                }
            }
        }
    }
    
    // Sort word frequencies in descending order using bubble sort
    for (int i = 0; i < uniqueWords - 1; i++) {
        for (int j = 0; j < uniqueWords - i - 1; j++) {
            if (wordFreqs[j].frequency < wordFreqs[j + 1].frequency) {
                WordFreq temp = wordFreqs[j];
                wordFreqs[j] = wordFreqs[j + 1];
                wordFreqs[j + 1] = temp;
            }
        }
    }
    
    // Print top words and their frequencies
    cout << "\n(**) Top " << TOP_WORDS << " words in fake government news articles:\n";
    for (int i = 0; i < min(TOP_WORDS, uniqueWords); i++) {
        cout << setw(20) << left << wordFreqs[i].word 
             << ": " << wordFreqs[i].frequency << " occurrences\n";
    }
}