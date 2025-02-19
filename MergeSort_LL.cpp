#include "MergeSort_LL.hpp"
#include <iostream>
#include <chrono>

// Function to split the list into two halves
void splitList(Article* head, Article** left, Article** right) {
    if (!head || !head->next) {
        *left = head;
        *right = nullptr;
        return;
    }
    Article* slow = head;
    Article* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

// Merge two sorted linked lists
Article* merge(Article* left, Article* right) {
    if (!left) return right;
    if (!right) return left;
    
    Article* result = nullptr;
    if (left->subject < right->subject) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

// Merge Sort function
Article* mergeSort(Article* head) {
    if (!head || !head->next) return head;
    
    Article *left, *right;
    splitList(head, &left, &right);
    
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
}

// // Function to count total articles in a linked list
// int countArticles(Article* head) {
//     int count = 0;
//     while (head) {
//         count++;
//         head = head->next;
//     }
//     return count;
// }

// Function to measure sorting time and memory usage
void measureMSTimeAndMemory(Article*& head) {
    using namespace std::chrono;
    
    // Measure time
    auto start = high_resolution_clock::now();
    head = mergeSort(head);
    auto end = high_resolution_clock::now();
    
    // Calculate and display elapsed time
    duration<double> duration = end - start;
    std::cout << "Sorting took: " << duration.count() << " seconds" << std::endl;
    
    // Count total articles
    int totalArticles = countArticles(head);
    std::cout << "Total Articles: " << totalArticles << std::endl;
    
    // Estimate memory usage
    size_t memoryUsage = sizeof(Article) * totalArticles;
    std::cout << "Memory usage: " << memoryUsage / (1024 * 1024) << " MB" << std::endl;
}

// Function to count articles per subject using a linked list (no unordered_map)
void countArticlesPerSubject(Article* head, const std::string& datasetName) {
    struct SubjectCountNode {
        std::string subject;
        int count;
        SubjectCountNode* next;
        SubjectCountNode(std::string s) : subject(s), count(1), next(nullptr) {}
    };
    
    SubjectCountNode* subjectHead = nullptr;
    Article* temp = head;
    while (temp) {
        std::string subject = temp->subject;
        SubjectCountNode* current = subjectHead;
        SubjectCountNode* prev = nullptr;
        while (current && current->subject < subject) {
            prev = current;
            current = current->next;
        }
        if (current && current->subject == subject) {
            current->count++;
        } else {
            SubjectCountNode* newNode = new SubjectCountNode(subject);
            if (!prev) {
                newNode->next = subjectHead;
                subjectHead = newNode;
            } else {
                newNode->next = current;
                prev->next = newNode;
            }
        }
        temp = temp->next;
    }
    
    // Print results
    std::cout << "\nArticles per subject in " << datasetName << " dataset:" << std::endl;
    SubjectCountNode* current = subjectHead;
    while (current) {
        std::cout << "Subject: " << current->subject << " - " << current->count << " Articles" << std::endl;
        SubjectCountNode* temp = current;
        current = current->next;
        delete temp;
    }
}
