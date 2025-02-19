#include "bubblesort_LL.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream> 

using namespace std;
using namespace std::chrono;



// Function to extract the year from the article's date (without comma)
int extractYear(const string& date) {
    string trimmedDate = trim(date);  // Ensure no leading/trailing spaces
    size_t lastSpace = trimmedDate.find_last_of(' ');  // Find the last space
    if (lastSpace == string::npos) return 0;  // Return 0 if no space found

    string yearStr = trimmedDate.substr(lastSpace + 1); // Extract year
    
    // Check if the year string is numeric and has exactly 4 digits
    if (yearStr.length() == 4 && all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
        return stoi(yearStr); // Return the year as an integer
    }

    return 0;  // Return 0 for invalid year format
}

// Bubble sort for linked list based on the year (Ascending Order)
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

            // Only swap if both years are valid
            if (year1 > 0 && year2 > 0 && year1 < year2) { 
                swap(ptr->title, ptr->next->title);
                swap(ptr->date, ptr->next->date);
                swap(ptr->subject, ptr->next->subject);
                swap(ptr->content, ptr->next->content);
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastSorted = ptr;
    } while (swapped);
}



int countValidArticles(Article* head) {
    int count = 0;
    while (head) {
        if (extractYear(head->date) > 0) {
            count++;  // Count only valid dates
        }
        head = head->next;
    }
    return count;
}


// Function to count total articles in a linked list
int countArticles(Article* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Function to measure sorting time and memory usage (basic version)
void measureTimeAndMemory(Article*& head) {
    using namespace std::chrono;
    
    // Measure time
    auto start = high_resolution_clock::now();
    bubbleSort(head);
    auto end = high_resolution_clock::now();
    
    // Calculate and display elapsed time
    duration<double> duration = end - start;
    std::cout << "Sorting took: " << duration.count() << " seconds" << std::endl;

    // Count total articles
    int totalValidArticles = countValidArticles(head);
    std::cout << "Total valid Articles: " << totalValidArticles << std::endl;

    // Estimate memory usage (size of each article object)
    size_t memoryUsage = sizeof(Article) * totalValidArticles;
    std::cout << "Memory usage: " << memoryUsage / (1024 * 1024) << " MB" << std::endl;  // In MB
}

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

    // Find the last node (tail) to start writing from the end
    Article* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    int lastYear = -1;

    // Traverse the list from tail to head in reverse order
    while (tail) {
        int year = extractYear(tail->date);

        // Ensure we only print valid years
        if (year > 0) {
            if (year != lastYear) {
                if (lastYear != -1) {
                    outFile << endl;  // Space between different years
                }
                outFile << "Year: " << year << endl;
                lastYear = year;
            }

            outFile << "  Title: " << tail->title << endl;
            outFile << "  Date: " << tail->date << endl;
            outFile << "--------------------------------------" << endl;
        }

        // Move tail backwards to the previous node
        Article* prev = head;
        while (prev && prev->next != tail) {
            prev = prev->next;
        }
        tail = (tail == head) ? nullptr : prev;  // Stop when we reach the head
    }

    outFile.close();
    cout << "Sorted articles have been stored in " << filename << " in ascending order." << endl;
}




