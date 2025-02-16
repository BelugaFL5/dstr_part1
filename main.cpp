#include <iostream>
#include <iomanip>
#include "LinearSearch_Array.hpp"
#include "HashSearch_Array.hpp"

using namespace std;

int main() {
    int fakeCount = 0, trueCount = 0;

    // Read CSV and store articles in arrays
    Article* fakeArticles = readCSV("data-fake.csv", fakeCount, true);
    Article* trueArticles = readCSV("data-true.csv", trueCount, false);

    /* cout << "\n(**) READ INTO ARRAY:" << endl;
    cout << "(*) Successfully stored " << fakeCount << " articles from data-fake.csv" << endl;
    cout << "(*) Successfully stored " << trueCount << " articles from data-true.csv" << endl;

    // **Calculate percentage of fake political news for each month in 2016**
    linearSearch_Array(fakeArticles, fakeCount, trueArticles, trueCount); */

    // **Frequent words in government-related news**
    analyzeContent_Array(fakeArticles, fakeCount);

    // Free dynamically allocated memory
    delete[] fakeArticles;
    delete[] trueArticles;

    return 0;
}

// COPY AND RUN IN TERMINAL:
// g++ main.cpp CSVHandling_Array.cpp LinearSearch_Array.cpp -o main
// ./main