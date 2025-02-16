#include "ArticleCounter.hpp"
#include "bubblesort_LL.hpp"  
#include <iostream>

// Function to count articles per year using a linked list instead of map
void countArticlesPerYear(Article* head, const std::string& datasetName) {
    YearCountNode* yearHead = nullptr; // Linked list to store year count

    Article* temp = head;
    while (temp) {
        int year = extractYear(temp->date); // Get the year from the date
        if (year > 0) {  // Only count valid years
            insertOrUpdateYearCount(yearHead, year); // Insert/update the count in the linked list
        }
        temp = temp->next;
    }

    // Print out the year counts
    std::cout << "\nArticles per year in " << datasetName << " dataset:" << std::endl;
    YearCountNode* current = yearHead;
    while (current) {
        std::cout << "Year " << current->year << ": " << current->count << " Articles" << std::endl;
        current = current->next;
    }

    // Cleanup the linked list
    while (yearHead) {
        YearCountNode* temp = yearHead;
        yearHead = yearHead->next;
        delete temp;
    }
}

// Helper function to insert or update year count in the linked list
void insertOrUpdateYearCount(YearCountNode*& head, int year) {
    YearCountNode* current = head;
    YearCountNode* previous = nullptr;

    // Check if the year already exists in the list
    while (current && current->year > year) {
        previous = current;
        current = current->next;
    }

    if (current && current->year == year) {
        // Year found, just increment the count
        current->count++;
    } else {
        // Year not found, create a new node and insert it
        YearCountNode* newNode = new YearCountNode(year);
        if (previous == nullptr) {
            // Insert at the beginning
            newNode->next = head;
            head = newNode;
        } else {
            // Insert in the middle or end
            newNode->next = current;
            previous->next = newNode;
        }
    }
}
