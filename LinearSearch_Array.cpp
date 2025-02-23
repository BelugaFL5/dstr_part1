#include "CSVHandling_Array.hpp"
#include <regex>
#include <iomanip>
#include <chrono>
#include <fstream>

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

// Function to check if the article belongs to a specific category
bool isCategory(const string& subject, const string& category) {
    if (category == "news") {
        return subject == "news"; // Match only if subject is exactly "news"
    }
    return regex_search(subject, regex(category, regex_constants::icase));
}

// Function to calculate the total fake political news percentage from fake articles over total fake and true articles in 2016
double totalNewsPercentage(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    int totalFakePoliticalArticles = 0;
    int totalTruePoliticalArticles = 0;

    // Process fake articles
    for (int i = 0; i < fakeSize; i++) {
        if (extractYear(fakeArr[i].date) == 2016) {
            if (isCategory(fakeArr[i].subject, "politics")) {
                totalFakePoliticalArticles++;
            }
        }
    }

    // Process true articles
    for (int i = 0; i < trueSize; i++) {
        if (extractYear(trueArr[i].date) == 2016) {
            if (isCategory(trueArr[i].subject, "politics")) {
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

    return fakePoliticalPercentage;  // Return the percentage of fake political news
}

// Function to search for political news in 2016 and display the percentage for each month
void trackNews_Array(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    auto start = startTimer();  // Start time measurement

    int politicalArticles_perMonth[12] = {0}; // Track total political articles (fake + true) per month
    int fakePoliticalArticles_perMonth[12] = {0}; // Track only fake political articles per month

    // Process fake political articles
    for (int i = 0; i < fakeSize; i++) {
        if (extractYear(fakeArr[i].date) == 2016 && isCategory(fakeArr[i].subject, "politics")) {
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
        if (extractYear(trueArr[i].date) == 2016 && isCategory(trueArr[i].subject, "politics")) {
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

    // Display elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "\nTime taken for linear search: " << elapsedTime << "ms" << endl;

    // Display memory usage
    size_t memoryUsage = calcMemoryUsage(fakeSize, trueSize);
    cout << "Memory usage taken for linear search: " << memoryUsage / (1024.0 * 1024.0) << "MB" << endl;
}

int getMonthValue(const string& month) {
    const string months[] = {
        "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
    };
    for (int i = 0; i < 12; i++) {
        if (months[i] == month) return i + 1;
    }
    return 0;
}

// Function to search for news articles by category and save results to a file
void linearSearchByCategory(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    int categoryChoice, searchType;
    string selectedCategory;

    cout << "\nSearch through:\n";
    cout << "1. Fake Articles\n";
    cout << "2. True Articles\n";
    cout << "Enter choice: ";
    cin >> searchType;

    Article* arr;
    int size;

    if (searchType == 1) {
        arr = fakeArr;
        size = fakeSize;

        cout << "\nSelect Category:\n";
        cout << "1. Government News\n";
        cout << "2. Left News\n";
        cout << "3. Middle East News\n";
        cout << "4. US News\n";
        cout << "5. General News\n";
        cout << "6. Politics\n";
        cout << "Enter choice: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1: selectedCategory = "government"; break;
            case 2: selectedCategory = "left"; break;
            case 3: selectedCategory = "middle"; break;
            case 4: selectedCategory = "us"; break;
            case 5: selectedCategory = "news"; break;
            case 6: selectedCategory = "politics"; break;
            default: cout << "Invalid choice. Exiting.\n"; return;
        }
    } 
    else if (searchType == 2) {
        arr = trueArr;
        size = trueSize;

        cout << "\nSelect Category:\n";
        cout << "1. Politics News\n";
        cout << "2. World News\n";
        cout << "Enter choice: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1: selectedCategory = "politicsnews"; break;
            case 2: selectedCategory = "worldnews"; break;
            default: cout << "Invalid choice. Exiting.\n"; return;
        }
    } 
    else {
        cout << "Invalid choice. Exiting.\n";
        return;
    }

    auto startSearch = startTimer();  // Start search time measurement

    // Open file to save results
    ofstream outFile("searchResults.txt");
    if (!outFile) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    int count = 0;

    // Search and save results
    for (int i = 0; i < size; i++) {
        if (isCategory(arr[i].subject, selectedCategory)) {
            outFile << "Title: " << arr[i].title << "\n";
            outFile << "Category: " << arr[i].subject << "\n";
            outFile << "Date: " << arr[i].date << "\n\n";
            count++;
        }
    }

    double searchTime = calcElapsedTime(startSearch);
    cout << "\nTime taken for searching: " << fixed << setprecision(1) << searchTime << "ms" << endl;

    size_t memoryUsage = calcMemoryUsage(count);
    cout << "Memory usage for search results: " << memoryUsage / (1024.0 * 1024.0) << " MB\n";

    if (count == 0) {
        outFile << "(?) No matching articles found.\n";
        cout << "(!) No articles found matching the search criteria.\n";
    } else {
        cout << "(**) " << count << " matching articles found and saved to searchResults.txt\n";
    }

    outFile.close();
}

// Function to search for news articles by year and save results to a file
void linearSearchByYear(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    int searchYear, searchType;
    cout << "\nEnter the year to search: ";
    cin >> searchYear;

    cout << "\nSearch through:\n";
    cout << "1. Fake Articles\n";
    cout << "2. True Articles\n";
    cout << "Enter choice: ";
    cin >> searchType;

    Article* arr;
    int size;

    if (searchType == 1) {
        arr = fakeArr;
        size = fakeSize;
    } else if (searchType == 2) {
        arr = trueArr;
        size = trueSize;
    } else {
        cout << "Invalid choice. Exiting.\n";
        return;
    }

    auto startSearch = startTimer();  // Start search time measurement

    // Open file to save results
    ofstream outFile("searchResults.txt");
    if (!outFile) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    int count = 0;

    // Search and save results
    for (int i = 0; i < size; i++) {
        if (extractYear(arr[i].date) == searchYear) {
            outFile << "Title: " << arr[i].title << "\n";
            outFile << "Category: " << arr[i].subject << "\n";
            outFile << "Date: " << arr[i].date << "\n\n";
            count++;
        }
    }

    double searchTime = calcElapsedTime(startSearch);
    cout << "\nTime taken for searching: " << fixed << setprecision(1) << searchTime << "ms" << endl;

    size_t memoryUsage = calcMemoryUsage(count);
    cout << "Memory usage for search results: " << memoryUsage / (1024.0 * 1024.0) << " MB\n";

    if (count == 0) {
        outFile << "(?) No matching articles found.\n";
        cout << "(!) No articles found matching the search criteria.\n";
    } else {
        cout << "(**) " << count << " matching articles found and saved to searchResults.txt\n";
    }

    outFile.close();
}

// Function to allow user to select search mode
void searchMenu(Article fakeArr[], int fakeSize, Article trueArr[], int trueSize) {
    int choice;
    cout << "\n\nSelect search mode:\n";
    cout << "1. Search by Category\n";
    cout << "2. Search by Year\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        linearSearchByCategory(fakeArr, fakeSize, trueArr, trueSize);
    } else if (choice == 2) {
        linearSearchByYear(fakeArr, fakeSize, trueArr, trueSize);
    } else {
        cout << "Invalid choice. Exiting.\n";
    }
}