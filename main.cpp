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
        cout << "\n(**) Fake Articles by Year:";
        countArticles_Bubble(fakeArticles, fakeCount);

        cout << "\n(**) True Articles by Year:";
        countArticles_Bubble(trueArticles, trueCount);

        // Display article counts by year using heap sort
        cout << "\n(**) Fake Articles by Year:";
        countArticles_Heap(fakeArticles, fakeCount);

        cout << "\n(**) True Articles by Year:";
        countArticles_Heap(trueArticles, trueCount);
    
        // Display article counts by year using merge sort
        cout << "\n(**) Fake Articles by Year:";
        countArticles_Merge(fakeArticles, fakeCount);

        cout << "\n(**) True Articles by Year:";
        countArticles_Merge(trueArticles, trueCount);

        // Store sorted articles in text files using bubblesort
        saveSortedArticlesToFile(fakeArticles,fakeCount, "sorted_fake_year_Array.txt");
        saveSortedArticlesToFile(trueArticles,trueCount, "sorted_true_year_Array.txt");

        // Store sorted articles in text files using mergesort
        storeSortedArticlesBySubject(fakeArticles, "sorted_fake_subjects_Array.txt");
        storeSortedArticlesBySubject(trueArticles, "sorted_true_subjects_Array.txt");

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