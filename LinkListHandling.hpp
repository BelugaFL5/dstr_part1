#ifndef LINKLISTHANDLING_HPP
#define LINKLISTHANDLING_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct Article {
    string title, content, subject, date;
    Article* next;
};

// Function prototypes (declarations only!)
string trim(string str);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues = false);
void displayArticles(Article* head, int count);
void deleteList(Article*& head);


#endif // LinkListHandling.HPP
