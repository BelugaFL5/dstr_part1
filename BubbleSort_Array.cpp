#include "CSVHandling_Array.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>

using namespace std;

// Function to calculate additional memory usage for Bubble Sort
size_t calcBubbleSortMemoryUsage() {
    // Bubble Sort is in-place, so no additional memory is used
    return 0;
}

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
    // Bubble sort algorithm for integers
    void bubbleSort(int arr[], int n) {
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

    // Bubble sort algorithm for Article objects
    void bubbleSort(Article arr[], int n) {
        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (extractYear(arr[j].date) > extractYear(arr[j + 1].date)) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            // If no two elements were swapped in the inner loop, break
            if (!swapped) break;
        }
    }
};

// Function to sort articles by year and export the results to a text file
void sortArticlesByYear_Bubble(Article* articles, int articleCount, const string& outputFileName) {
    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    // Use a dynamic array to hold the articles
    DynamicArray<Article> articleArray;
    for (int i = 0; i < articleCount; i++) {
        articleArray.push_back(articles[i]);
    }

    // Sort the articles by year using bubble sort
    articleArray.sort();

    // Open a file for writing the sorted results
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << outputFileName << " for writing." << endl;
        return;
    }

    // Write the sorted results to the file
    outputFile << "Articles sorted by year:\n";
    for (int i = 0; i < articleArray.getSize(); i++) {
        outputFile << "Year: " << extractYear(articleArray[i].date) << ", Title: " << articleArray[i].title << endl;
    }
    outputFile.close();

    // Display a confirmation message
    cout << "\nSorted results have been exported to " << outputFileName << endl;

    // Calculate elapsed time
    double elapsedTime = calcElapsedTime(start);
    cout << "\nTime taken for bubble sort: " << fixed << setprecision(2) << elapsedTime << "ms" << endl;

    // Calculate memory usage for the input array
    size_t inputMemoryUsage = calcMemoryUsage(articles, articleCount);

    // Calculate additional memory usage for Bubble Sort
    size_t bubbleSortMemoryUsage = calcBubbleSortMemoryUsage();

    // Total memory usage
    size_t totalMemoryUsage = inputMemoryUsage + bubbleSortMemoryUsage;

    cout << "Memory usage for bubble sort: " << totalMemoryUsage / (1024.0 * 1024.0) << " MB" << endl;
}

// Function to count the number of articles per year
void countArticles_Bubble(Article* articles, int articleCount) {
    
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

    // Sort the years using bubble sort
    years.sort();

    // Display the results sorted by year
    cout << "\n";
    for (int i = 0; i < years.getSize(); i++) {
        cout << years[i] << ": " << counts[i] << " articles" << endl;
    }

   }