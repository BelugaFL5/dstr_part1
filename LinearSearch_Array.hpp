#ifndef LINEARSEARCH_ARRAY_HPP
#define LINEARSEARCH_ARRAY_HPP

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <string>

using namespace std;

// Function declarations
int extractYear(string date);
bool isPolitical(const string& subject);
void printDashes(double percentage);
double totalNewsPercentage(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);
void linearSearch_Array(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize);

#endif // LINEARSEARCH_ARRAY_HPP