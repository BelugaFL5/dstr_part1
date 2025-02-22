#include <iostream>
#include <iomanip>
#include "LinearSearch_Array.hpp"
#include "HashSearch_Array.hpp"
#include "BubbleSort_Array.hpp"
#include "HeapSort_Array.hpp"
#include "MergeSort_Array.hpp"

using namespace std;

int main() {
    int fakeCount = 0, trueCount = 0;

    cout << "\n(**) READ INTO ARRAY:" << endl;
    // Read CSV and store articles into array, and display number of articles
    Article* fakeArticles = readCSV("data-fake.csv", fakeCount, true);
    Article* trueArticles = readCSV("data-true.csv", trueCount, false);

     // Display article counts by year
     cout << "\n(**) Fake Articles by Year(Bubble Sort):";
     sortArticlesByYear_Bubble(fakeArticles, fakeCount,"sortBubble_fake_year_Array.txt");
 
     cout << "\n(**) True Articles by Year(Bubble Sort):";
     sortArticlesByYear_Bubble(trueArticles, trueCount,"sortBubble_true_year_Array.txt");
 

    // Display article counts by Subject
    cout << "\n(**) Fake Articles by Subject(Heap Sort):\n";
    sortArticlesBySubject_Heap(fakeArticles, fakeCount, "sortHeap_fake_subjects_Array.txt");
    cout << "\n(**) True Articles by Subject(Heap Sort):\n";
    sortArticlesBySubject_Heap(trueArticles, trueCount,"sortHeap_fake_subjects_Array.txt");
//LOVE YOU MUMMY
    cout << "\n(**) Fake Articles by Subject(Merge Sort):\n";
    sortArticlesBySubject_Merge(fakeArticles, fakeCount,"sortMerge_fake_subjects_Array.txt");


    cout << "\n(**) True Articles by Subject(Merge Sort):\n";
    sortArticlesBySubject_Merge(trueArticles, trueCount,"sortMerge_true_subjects_Array.txt");

    // Calculate percentage of fake political news for each month in 2016
    trackNews_Array(fakeArticles, fakeCount, trueArticles, trueCount);

    // Frequent words in government-related news
    analyzeContent_Array(fakeArticles, fakeCount);

    // Display search menu
    searchMenu(fakeArticles, fakeCount, trueArticles, trueCount);

    // Free dynamically allocated memory
    delete[] fakeArticles;
    delete[] trueArticles;

    return 0;
}

// g++ CSVHandling_Array.cpp HashSearch_Array.cpp main.cpp LinearSearch_Array.cpp BubbleSort_Array.cpp HeapSort_Array.cpp MergeSort_Array.cpp -o main
// ./main