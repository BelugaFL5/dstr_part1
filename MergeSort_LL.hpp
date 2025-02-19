#ifndef MERGESORT_LL_HPP
#define MERGESORT_LL_HPP

#include "LinkListHandling.hpp"  // Ensures access to the Article struct
#include "BubbleSort_LL.hpp"

// Function to sort articles by subject using Merge Sort
Article* mergeSort(Article* head);
void countArticlesPerSubject(Article* head, const std::string& datasetName);
int countArticles(Article* head);
void storeSortedArticlesBySubject(Article* head, const string& filename);

#endif // MERGESORT_LL_HPP
