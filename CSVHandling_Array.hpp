#ifndef CSVHANDLING_ARRAY_HPP
#define CSVHANDLING_ARRAY_HPP

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

struct Article {
    string title, content, subject, date;
};

std::chrono::high_resolution_clock::time_point startTimer();
double calculateElapsedTime(std::chrono::high_resolution_clock::time_point start);
size_t calculateMemoryUsage(int fakeSize, int trueSize);
string trim(string str);
void convertMonthToShortForm(string& date);
void parseCSVLine(const string& line, string fields[4]);
Article* readCSV(const string& inputFile, int& count, bool trackIssues);

#endif // CSVHANDLING_ARRAY_HPP
