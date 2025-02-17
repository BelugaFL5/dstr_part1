#include "LinkListHandling.hpp"
#include "BubbleSort_LL.hpp"
#include "ArticleCounter.hpp"
#include <iostream>

using namespace std;

int main() {
    int fakeCount = 0, trueCount = 0;

    // Read CSV files into linked lists
    Article* fakeHead = readCSV("data-fake.csv", fakeCount, true);
    Article* trueHead = readCSV("data-true.csv", trueCount, false);

    cout << "\n\n(**) READ INTO LINKED LIST:" << endl;
    cout << "(*) Successfully stored " << fakeCount << " articles from data-fake.csv" << endl;
    cout << "(*) Successfully stored " << trueCount << " articles from data-true.csv" << endl;

    // Display total number of articles in each dataset
    cout << "\nTotal Articles Count:" << endl;
    cout << "Fake News Dataset: " << countArticles(fakeHead) << " articles" << endl;
    cout << "True News Dataset: " << countArticles(trueHead) << " articles" << endl;

    // Measure time and memory for sorting articles in fake dataset
    cout << "\nMeasuring time and memory for sorting fake dataset..." << endl;
    measureTimeAndMemory(fakeHead);

    // Measure time and memory for sorting articles in true dataset
    cout << "\nMeasuring time and memory for sorting true dataset..." << endl;
    measureTimeAndMemory(trueHead);

    // Sorting articles by year
    cout << "\nSorting articles by year..." << endl;
    bubbleSort(fakeHead);
    bubbleSort(trueHead);
    cout << "(*) Sorting completed!" << endl;

    // Display articles per year for both datasets using the modified linked list approach
    countArticlesPerYear(fakeHead, "Fake News");
    countArticlesPerYear(trueHead, "True News");

    // Cleanup linked lists
    deleteList(fakeHead);
    deleteList(trueHead);

    cout << "\n(*) Memory cleanup completed. Exiting program.\n";
    return 0;
}
