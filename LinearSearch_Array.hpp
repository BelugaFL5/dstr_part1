#ifndef LINEARSEARCH_ARRAY_HPP
#define LINEARSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>

using namespace std;

// Function declarations
void printDashes(double percentage);
bool isCategory(const string& subject, const string& category);
string regex_escape(const string& input);
double totalNewsPercentage(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
int getMonthValue(const string& month);
void saveSortedResults(Article articles[], int size, const string& selectedCategory, int searchYear = -1);
void trackNews_Array(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
void linearSearchByCategory(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
void linearSearchByYear(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
void searchMenu(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);

#endif // LINEARSEARCH_ARRAY_HPP