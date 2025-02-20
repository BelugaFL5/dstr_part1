#include "bubblesort_LL.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream> 
#include "MergeSort_LL.hpp"

using namespace std;
using namespace std::chrono;

// Function to extract the year from an article's date
int extractYear(const string& date) {
    string trimmedDate = trim(date);  // Remove leading/trailing spaces
    size_t lastSpace = trimmedDate.find_last_of(' ');  // Find the last space
    
    if (lastSpace == string::npos) return 0;  // Return 0 if no space found

    string yearStr = trimmedDate.substr(lastSpace + 1); // Extract year
    
    // Check if the year has exactly 4 digits and is numeric
    return (yearStr.length() == 4 && all_of(yearStr.begin(), yearStr.end(), ::isdigit)) ? stoi(yearStr) : 0;
}

// Bubble Sort for linked list based on article year (descending Order)
void bubbleSort(Article*& head) {
    if (!head || !head->next) return;

    bool swapped;
    Article* ptr;
    Article* lastSorted = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != lastSorted) {
            int year1 = extractYear(ptr->date);
            int year2 = extractYear(ptr->next->date);

            // Swap only if years are valid and out of order
            if (year1 > 0 && year2 > 0 && year1 < year2) { 
                swap(ptr->title, ptr->next->title);
                swap(ptr->date, ptr->next->date);
                swap(ptr->subject, ptr->next->subject);
                swap(ptr->content, ptr->next->content);
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastSorted = ptr;  // Mark last sorted element
    } while (swapped);
}

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
    while (current && current->year > year) { // Ensure descending order
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



// Count articles with valid years
int countValidArticles(Article* head) {
    int count = 0;
    while (head) {
        if (extractYear(head->date) > 0) {
            count++;  // Only count valid articles
        }
        head = head->next;
    }
    return count;
}



// Store sorted articles in a file (Ascending Order)
void storeSortedArticlesToFile(Article* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    if (!head) {
        cerr << "No articles to write!" << endl;
        return;
    }

    // Find the last node to write from end to start
    Article* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    int lastYear = -1;

    // Traverse in reverse order
    while (tail) {
        int year = extractYear(tail->date);

        if (year > 0) {
            if (year != lastYear) {
                if (lastYear != -1) outFile << endl;  // Separate different years
                outFile << "Year: " << year << endl;
                lastYear = year;
            }

            outFile << "  Title: " << tail->title << endl;
            outFile << "  Date: " << tail->date << endl;
            outFile << "--------------------------------------" << endl;
        }

        // Move tail backwards
        Article* prev = head;
        while (prev && prev->next != tail) {
            prev = prev->next;
        }
        tail = (tail == head) ? nullptr : prev;  // Stop when reaching head
    }

    outFile.close();
    cout << "Sorted articles have been stored in " << filename << "." << endl;
}
