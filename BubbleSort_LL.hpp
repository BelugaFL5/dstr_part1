#ifndef BUBBLESORT_LL_HPP
#define BUBBLESORT_LL_HPP

#include "LinkListHandling.hpp"


struct YearCountNode {
    int year;
    int count;
    YearCountNode* next;

    YearCountNode(int y) : year(y), count(1), next(nullptr) {}  // Constructor
};



// Function prototypes
void bubbleSort(Article*& head);
int extractYear(const std::string& date);
int countValidArticles(Article* head);
void storeSortedArticlesToFile(Article* head, const string& filename); 
void countArticlesPerYear(Article* head, const std::string& datasetName);
void insertOrUpdateYearCount(YearCountNode*& head, int year);





#endif
