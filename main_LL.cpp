#include <iostream>
#include "BubbleSort_LL.hpp"

using namespace std;

int main() {
    int fakeCount = 0, trueCount = 0;

    // Load news articles into linked lists
    Article* fakeHead = readCSV("data-fake.csv", fakeCount, true);
    Article* trueHead = readCSV("data-true.csv", trueCount, false);

    cout << "\nBefore Sorting Fake News:\n";
    displayArticles(fakeHead, 3);  // Show first 5 fake articles
    cout << "\nBefore Sorting True News:\n";
    displayArticles(trueHead, 3);  // Show first 5 true articles

    // **Sort both linked lists by year (ascending)**
    bubbleSort(fakeHead);
    bubbleSort(trueHead);

    cout << "\nFake News After Sorting by Year:\n";
    displayArticles(fakeHead, 3);  // Show first 5 fake articles after sorting
    cout << "\nTrue News After Sorting by Year:\n";
    displayArticles(trueHead, 3);  // Show first 5 true articles after sorting

    // Display total number of articles
    cout << "\nTotal Articles in Fake News Dataset: " << fakeCount << endl;
    cout << "Total Articles in True News Dataset: " << trueCount << endl;

    // Clean up memory (delete linked list nodes)
    deleteList(fakeHead);
    deleteList(trueHead);

    return 0;
}

// g++ -o main_LL main_LL.cpp LinkListHandling.cpp BubbleSort_LL.cpp
// ./main_LL