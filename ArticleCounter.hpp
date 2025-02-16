#ifndef ARTICLECOUNTER_HPP
#define ARTICLECOUNTER_HPP

#include "LinkListHandling.hpp"      
#include <iostream>    

// Function to count valid articles per year and store them in a custom linked list structure
void countArticlesPerYear(Article* head, const std::string& datasetName);

// Custom linked list structure to store year counts
struct YearCountNode {
    int year;
    int count;
    YearCountNode* next;
    
    YearCountNode(int y) : year(y), count(1), next(nullptr) {}
};

// Helper function to insert or update year count in the linked list
void insertOrUpdateYearCount(YearCountNode*& head, int year);

#endif
