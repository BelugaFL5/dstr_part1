// SIOW HAN BIN FOR Q1

#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

// Custom dynamic array class to simulate vector functionality
template <typename T>
class DynamicArray {
public:
    T* data;
    int size;
    int capacity;

    // Constructor
    DynamicArray(int initialCapacity = 10) {
        capacity = initialCapacity;
        size = 0;
        data = new T[capacity];
    }

    // Destructor
    ~DynamicArray() {
        delete[] data;
    }

    // Add an element to the array
    void push_back(const T& element) {
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = element;
    }

    // Get element at index
    T& operator[](int index) {
        return data[index];
    }

    // Get size of the array
    int getSize() const {
        return size;
    }

    // Sort the array (using bubble sort)
    void sort() {
        bubbleSort(data, size);
    }

private:
    // Bubble sort algorithm
    void bubbleSort(T arr[], int n) {
        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            // If no two elements were swapped in the inner loop, break
            if (!swapped) break;
        }
    }
};

// Function to count the number of articles per year
void countArticles_Bubble(Article* articles, int articleCount) {
    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Use a dynamic array to hold the year counts (similar to a map)
    DynamicArray<int> years;
    DynamicArray<int> counts;

    for (int i = 0; i < articleCount; i++) {
        int year = extractYear(articles[i].date);
        if (year > 0) {
            bool found = false;
            for (int j = 0; j < years.getSize(); j++) {
                if (years[j] == year) {
                    counts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                years.push_back(year);
                counts.push_back(1);
            }
        }
    }

    // Sort the years
    years.sort();

    // Display the results sorted by year
    cout << "\n";
    for (int i = 0; i < years.getSize(); i++) {
        cout << years[i] << ": " << counts[i] << " articles" << endl;
    }

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "Time taken for bubble sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;
}