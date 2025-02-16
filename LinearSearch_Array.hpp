#ifndef LINEARSEARCH_ARRAY_HPP
#define LINEARSEARCH_ARRAY_HPP

#include <iostream>
#include <string>
#include "CSVHandling_Array.hpp" // for Article struct

using namespace std;

// Declare function prototypes
int extractYear(string date);
bool isPolitical(const string& subject);
void printDashes(double percentage);
double totalNewsPercentage(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
void linearSearch_Array(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);

#endif // LINEARSEARCH_ARRAY_HPP
