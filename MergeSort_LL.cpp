#include "MergeSort_LL.hpp"
#include <iostream>
#include <chrono>

// Splits the linked list into two halves for merge sort
void splitList(Article* head, Article** left, Article** right) {
    if (!head || !head->next) {
        *left = head;
        *right = nullptr;
        return;
    }
    Article* slow = head;
    Article* fast = head->next;

    // Move fast pointer twice as fast as slow to find the middle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list into two halves
    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

// Merges two sorted linked lists based on subject
Article* merge(Article* left, Article* right) {
    if (!left) return right;
    if (!right) return left;
    
    // Select the smaller subject alphabetically
    if (left->subject < right->subject) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

// Merge Sort algorithm for sorting the linked list by subject
Article* mergeSort(Article* head) {
    if (!head || !head->next) return head;
    
    Article *left, *right;
    splitList(head, &left, &right);
    
    // Recursively sort both halves
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

// Counts articles per subject using a linked list (no built-in containers)
void countArticlesPerSubject(Article* head, const std::string& datasetName) {
    struct SubjectCountNode {
        std::string subject;
        int count;
        SubjectCountNode* next;
        SubjectCountNode(std::string s) : subject(s), count(1), next(nullptr) {}
    };
    
    SubjectCountNode* subjectHead = nullptr;
    Article* temp = head;

    // Traverse the sorted list and count subjects
    while (temp) {
        std::string subject = temp->subject;
        SubjectCountNode* current = subjectHead;
        SubjectCountNode* prev = nullptr;

        // Find the correct position for the subject
        while (current && current->subject < subject) {
            prev = current;
            current = current->next;
        }

        // If subject exists, increase count, otherwise insert new node
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

    // Print subject counts
    std::cout << "\nArticles per subject in " << datasetName << " dataset:" << std::endl;
    SubjectCountNode* current = subjectHead;
    while (current) {
        std::cout << "Subject: " << current->subject << " - " << current->count << " Articles" << std::endl;
        
        // Free allocated memory
        SubjectCountNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Stores sorted articles in a file grouped by subject
void storeSortedArticlesBySubject(Article* head, const string& filename) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    if (!head) {
        cerr << "No articles to write!" << endl;
        return;
    }

    string lastSubject = "";

    // Write articles to file, grouping by subject
    while (head) {
        if (head->subject != lastSubject) {
            if (!lastSubject.empty()) outFile << endl;
            outFile << "Subject: " << head->subject << endl;
            lastSubject = head->subject;
        }

        // Write article details
        outFile << "  Title: " << head->title << endl;
        outFile << "  Date: " << head->date << endl;
        outFile << "--------------------------------------" << endl;

        head = head->next;
    }

    outFile.close();
    cout << "Sorted articles by subject stored in " << filename << " (Ascending Order)." << endl;
}
