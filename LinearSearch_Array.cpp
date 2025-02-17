#include "CSVHandling_Array.hpp"
#include <regex>
#include <iomanip>
#include <chrono>

using namespace std;

// Function to calculate and represent percentage (== for the percentage and -- for the remainder)
void printDashes(double percentage) {
    percentage = max(0.0, min(100.0, percentage)); // Ensure percentage is within 0 and 100

    int numEqualSigns = static_cast<int>(percentage);  // Number of '=' based on percentage
    int numDashSigns = 100 - numEqualSigns;  // Remaining dashes to fill the line

    // If percentage is 0, just print dashes
    if (percentage == 0) {
        for (int i = 0; i < 100; i++) {
            cout << "-";
        }
    } else {
        // Print '=' for the percentage
        for (int i = 0; i < numEqualSigns; i++) {
            cout << "=";
        }
        
        // Print '-' for the remaining portion
        for (int i = 0; i < numDashSigns; i++) {
            cout << "-";
        }
    }
}

// Function to extract the year from the article's date
int extractYear(string date) {
    date = trim(date);  // Ensure no leading/trailing spaces
    size_t lastSpace = date.find_last_of(' ');
    if (lastSpace == string::npos) return 0;  // Error case
    string yearStr = date.substr(lastSpace + 1); // Extract year
    try {
        return stoi(yearStr); // Convert to integer
    } catch (...) {
        return 0;  // Handle errors
    }
}

// Function to check if the article is political
bool isPolitical(const string& subject) {
    return regex_search(subject, regex("politics", regex_constants::icase));
}

// Function to calculate the total fake political news percentage from fake articles over total fake and true articles in 2016
double totalNewsPercentage(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    int totalFakePoliticalArticles = 0;
    int totalTruePoliticalArticles = 0;

    // Process fake articles
    for (int i = 0; i < fakeSize; i++) {
        if (extractYear(fakeArr[i].date) == 2016) {
            if (isPolitical(fakeArr[i].subject)) {
                totalFakePoliticalArticles++;
            }
        }
    }

    // Process true articles
    for (int i = 0; i < trueSize; i++) {
        if (extractYear(trueArr[i].date) == 2016) {
            if (isPolitical(trueArr[i].subject)) {
                totalTruePoliticalArticles++;
            }
        }
    }

    int totalPoliticalArticles = totalFakePoliticalArticles + totalTruePoliticalArticles;
    
    // Calculate percentage of fake political news over total political articles
    double fakePoliticalPercentage = 0;
    if (totalPoliticalArticles > 0) {
        fakePoliticalPercentage = (static_cast<double>(totalFakePoliticalArticles) / totalPoliticalArticles) * 100.0;
    }

    return fakePoliticalPercentage;
}

// Function to search for political news in 2016 and display the percentage for each month
void linearSearch_Array(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    auto start = startTimer();  // Start time measurement

    int politicalArticles_perMonth[12] = {0}; // Track total political articles (fake + true) per month
    int fakePoliticalArticles_perMonth[12] = {0}; // Track only fake political articles per month

    // Process fake political articles
    for (int i = 0; i < fakeSize; i++) {
        if (extractYear(fakeArr[i].date) == 2016 && isPolitical(fakeArr[i].subject)) {
            size_t firstSpace = fakeArr[i].date.find(' ');
            string month = fakeArr[i].date.substr(0, firstSpace);
            
            if (month == "jan") {
                politicalArticles_perMonth[0]++;
                fakePoliticalArticles_perMonth[0]++;
            }
            else if (month == "feb") {
                politicalArticles_perMonth[1]++;
                fakePoliticalArticles_perMonth[1]++;
            }
            else if (month == "mar") {
                politicalArticles_perMonth[2]++;
                fakePoliticalArticles_perMonth[2]++;
            }
            else if (month == "apr") {
                politicalArticles_perMonth[3]++;
                fakePoliticalArticles_perMonth[3]++;
            }
            else if (month == "may") {
                politicalArticles_perMonth[4]++;
                fakePoliticalArticles_perMonth[4]++;
            }
            else if (month == "jun") {
                politicalArticles_perMonth[5]++;
                fakePoliticalArticles_perMonth[5]++;
            }
            else if (month == "jul") {
                politicalArticles_perMonth[6]++;
                fakePoliticalArticles_perMonth[6]++;
            }
            else if (month == "aug") {
                politicalArticles_perMonth[7]++;
                fakePoliticalArticles_perMonth[7]++;
            }
            else if (month == "sep") {
                politicalArticles_perMonth[8]++;
                fakePoliticalArticles_perMonth[8]++;
            }
            else if (month == "oct") {
                politicalArticles_perMonth[9]++;
                fakePoliticalArticles_perMonth[9]++;
            }
            else if (month == "nov") {
                politicalArticles_perMonth[10]++;
                fakePoliticalArticles_perMonth[10]++;
            }
            else if (month == "dec") {
                politicalArticles_perMonth[11]++;
                fakePoliticalArticles_perMonth[11]++;
            }
        }
    }

    // Process true political articles
    for (int i = 0; i < trueSize; i++) {
        if (extractYear(trueArr[i].date) == 2016 && isPolitical(trueArr[i].subject)) {
            size_t firstSpace = trueArr[i].date.find(' ');
            string month = trueArr[i].date.substr(0, firstSpace);
            
            if (month == "jan") politicalArticles_perMonth[0]++;
            else if (month == "feb") politicalArticles_perMonth[1]++;
            else if (month == "mar") politicalArticles_perMonth[2]++;
            else if (month == "apr") politicalArticles_perMonth[3]++;
            else if (month == "may") politicalArticles_perMonth[4]++;
            else if (month == "jun") politicalArticles_perMonth[5]++;
            else if (month == "jul") politicalArticles_perMonth[6]++;
            else if (month == "aug") politicalArticles_perMonth[7]++;
            else if (month == "sep") politicalArticles_perMonth[8]++;
            else if (month == "oct") politicalArticles_perMonth[9]++;
            else if (month == "nov") politicalArticles_perMonth[10]++;
            else if (month == "dec") politicalArticles_perMonth[11]++;
        }
    }

    // Output the percentage for each month
    cout << "\n(**) Fake Political News Articles in 2016 (Percentage by Month):\n";
    const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++) {
        if (politicalArticles_perMonth[i] > 0) {
            double percentage = (fakePoliticalArticles_perMonth[i] * 100.0) / politicalArticles_perMonth[i];
            cout << setw(12) << left << months[i] << " || "; 
            printDashes(percentage);  // Print the dashes
            cout << fixed << setprecision(1); // Round to 1 decimal point
            cout << " " << percentage << "%" << endl; // Print the percentage
        } else {
            cout << setw(12) << left << months[i] << " || "; 
            printDashes(0);  // Print the dashes
            cout << fixed << setprecision(1); // Round to 1 decimal point
            cout << " 0.0%" << endl; // Print the percentage
        }
    }

    // Calculate and print the total percentage of fake political news
    double totalFakePoliticalPercentage = totalNewsPercentage(fakeArr, fakeSize, trueArr, trueSize);
    cout << "\nPercentage of Political News Articles that are Fake in 2016: " << fixed << setprecision(1) << totalFakePoliticalPercentage << "%" << endl;

    // After processing articles, display elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "\nTime taken for linear search: " << elapsedTime << "s" << endl;

    // After processing articles, display memory usage
    size_t memoryUsage = calcMemoryUsage(fakeSize, trueSize);
    cout << "Memory usage taken for linear search: " << memoryUsage / (1024 * 1024) << "MB" << endl;
}