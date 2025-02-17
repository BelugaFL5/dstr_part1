#ifndef BUBBLESORT_LL_HPP
#define BUBBLESORT_LL_HPP

#include "LinkListHandling.hpp"

// Function prototypes
void bubbleSort(Article*& head);
int countArticles(Article* head);
int extractYear(const string& date);
int countValidArticles(Article* head);
void measureTimeAndMemory(Article*& head);
void storeSortedArticlesToFile(Article* head, const string& filename);


#endif

