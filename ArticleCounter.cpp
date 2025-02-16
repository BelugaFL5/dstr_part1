#include "ArticleCounter.hpp"
#include "bubblesort_LL.hpp"  

#include <map>
#include <iostream>

void countArticlesPerYear(Article* head, const std::string& datasetName) {
    std::map<int, int, std::greater<int>> yearCount; // Stores year -> count (descending)
    Article* temp = head;

    while (temp) {
        int year = extractYear(temp->date); // Use the extractYear function to handle invalid dates
        if (year > 0) {  // Only count valid years
            yearCount[year]++;
        }
        temp = temp->next;
    }

    std::cout << "\nArticles per year in " << datasetName << " dataset:" << std::endl;
    for (const auto& pair : yearCount) {
        std::cout << "Year " << pair.first << ": " << pair.second << " Articles" << std::endl;
    }
}
