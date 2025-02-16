#include "BubbleSort_LL.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

// Function to extract the year from the date field
int extractYear(const std::string& date) {
    if (isdigit(date[0]) && isdigit(date[1]) && isdigit(date[2]) && isdigit(date[3])) {
        return std::stoi(date.substr(0, 4));
    }

    std::istringstream ss(date);
    std::string month, day, year;
    ss >> month >> day >> year;

    if (!day.empty() && day.back() == ',') {
        day.pop_back();
    }

    for (char c : year) {
        if (!isdigit(c)) {
            std::cerr << "Error extracting year from date: " << date << std::endl;
            return 0;
        }
    }

    return std::stoi(year);
}

// ✅ Add bubbleSort implementation here
void bubbleSort(Article*& head) {
    if (!head || !head->next) return;

    bool swapped;
    Article* ptr;
    Article* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (extractYear(ptr->date) > extractYear(ptr->next->date)) {
                // Swap values instead of nodes
                std::swap(ptr->title, ptr->next->title);
                std::swap(ptr->content, ptr->next->content);
                std::swap(ptr->subject, ptr->next->subject);
                std::swap(ptr->date, ptr->next->date);
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}
